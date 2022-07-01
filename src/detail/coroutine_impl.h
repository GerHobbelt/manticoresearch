//
// Copyright (c) 2022, Manticore Software LTD (https://manticoresearch.com)
// Copyright (c) 2001-2016, Andrew Aksyonoff
// Copyright (c) 2008-2016, Sphinx Technologies Inc
// All rights reserved
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License. You should have
// received a copy of the GPL license along with this program; if you
// did not, you can find it at http://www.gnu.org
//

// that file includes implementation details from coroutine.h

namespace Threads
{

/////////////////////////////////////////////////////////////////////////////
/// ClonableCtx_T
/////////////////////////////////////////////////////////////////////////////

template<typename REFCONTEXT, typename CONTEXT>
template<typename... PARAMS>
ClonableCtx_T<REFCONTEXT, CONTEXT>::ClonableCtx_T ( PARAMS&&... tParams )
	: m_dParentContext ( std::forward<PARAMS> ( tParams )... )
{
	if ( !m_dParentContext.IsClonable() )
		return;

	int iContexts = NThreads() - 1;
	if ( !iContexts )
		return;

	Setup ( iContexts );
}

template<typename REFCONTEXT, typename CONTEXT>
void ClonableCtx_T<REFCONTEXT, CONTEXT>::LimitConcurrency ( int iDistThreads )
{
	assert ( m_iTasks == 0 ); // can be run only when no work started
	if ( !iDistThreads )	  // 0 as for dist_threads means 'no limit'
		return;

	auto iContexts = iDistThreads - 1; // one context is always clone-free
	if ( m_dChildrenContexts.GetLength() <= iContexts )
		return; // nothing to align

	Setup ( iContexts );
}

template<typename REFCONTEXT, typename CONTEXT>
ClonableCtx_T<REFCONTEXT, CONTEXT>::~ClonableCtx_T()
{
	for ( auto& tCtx : m_dChildrenContexts )
		tCtx.reset();
}

// called once per coroutine, when it really has to process something
template<typename REFCONTEXT, typename CONTEXT>
REFCONTEXT ClonableCtx_T<REFCONTEXT, CONTEXT>::CloneNewContext ( const int* pJobId )
{
	if ( m_bDisabled )
		return m_dParentContext;

	auto iMyIdx = m_iTasks.fetch_add ( 1, std::memory_order_acq_rel );
	if ( !iMyIdx )
		return m_dParentContext;

	--iMyIdx; // make it back 0-based
	auto& tCtx = m_dChildrenContexts[iMyIdx];
	tCtx.emplace_once ( m_dParentContext );
	m_dJobIds[iMyIdx] = pJobId ? *pJobId : 0;
	return (REFCONTEXT)m_dChildrenContexts[iMyIdx].get();
}

// Num of parallel workers to complete iTasks jobs
template<typename REFCONTEXT, typename CONTEXT>
inline int ClonableCtx_T<REFCONTEXT, CONTEXT>::Concurrency ( int iTasks )
{
	return Min ( m_dChildrenContexts.GetLength() + 1, iTasks ); // +1 since parent is also an extra context
}

template<typename REFCONTEXT, typename CONTEXT>
void ClonableCtx_T<REFCONTEXT, CONTEXT>::Setup ( int iContexts )
{
	m_dChildrenContexts.Reset ( iContexts );
	m_dJobIds.Reset ( iContexts );
	m_bDisabled = !iContexts;
}

template<typename REFCONTEXT, typename CONTEXT>
template<typename FNPROCESSOR>
void ClonableCtx_T<REFCONTEXT, CONTEXT>::ForAll ( FNPROCESSOR fnProcess, bool bIncludeRoot )
{
	if ( bIncludeRoot )
		fnProcess ( m_dParentContext );

	if ( m_bDisabled ) // nothing to do; sorters and results are already original
		return;

	CSphVector<std::pair<int, int>> dOrder;
	int iWorkThreads = m_iTasks - 1;
	for ( int i = 0; i < iWorkThreads; ++i )
		dOrder.Add ( { i, m_dJobIds[i] } );

	dOrder.Sort ( ::bind ( &std::pair<int, int>::second ) );
	for ( auto i : dOrder )
	{
		assert ( m_dChildrenContexts[i.first] );
		auto tCtx = (REFCONTEXT)m_dChildrenContexts[i.first].get();
		fnProcess ( tCtx );
	}
}

template<typename REFCONTEXT, typename CONTEXT>
void ClonableCtx_T<REFCONTEXT, CONTEXT>::Finalize()
{
	ForAll ( [this] ( REFCONTEXT tContext ) { m_dParentContext.MergeChild ( tContext ); }, false );
}

/////////////////////////////////////////////////////////////////////////////
/// ScopedScheduler_c
/////////////////////////////////////////////////////////////////////////////

inline ScopedScheduler_c::ScopedScheduler_c ( SchedRole pRole )
{
	if ( !pRole )
		return;

	m_pRoleRef = Coro::CurrentScheduler();
	//		if ( m_pRoleRef )
	AcquireSched ( pRole );
}

inline ScopedScheduler_c::ScopedScheduler_c ( RoledSchedulerSharedPtr_t& pRole )
{
	if ( !pRole )
		return;

	m_pRoleRef = Coro::CurrentScheduler();
	//		if ( m_pRoleRef )
	AcquireSched ( pRole );
}

inline ScopedScheduler_c::~ScopedScheduler_c()
{
	if ( m_pRoleRef )
		AcquireSched ( m_pRoleRef );
}


namespace Coro
{

// if iStack<0, just immediately invoke the handler (that is bypass)
template<typename HANDLER>
void Continue ( int iStack, HANDLER handler )
{
	if ( iStack<0 ) {
		handler ();
		return;
	}
	Continue ( handler, iStack );
}

// if iStack<0, just immediately invoke the handler (that is bypass). Returns boolean result from handler
template<typename HANDLER>
bool ContinueBool ( int iStack, HANDLER handler )
{
	if ( iStack<0 )
		return handler ();

	bool bResult;
	Continue ( [&bResult, fnHandler = std::move ( handler )] { bResult = fnHandler (); }, iStack );
	return bResult;
}

/////////////////////////////////////////////////////////////////////////////
/// ScopedScheduler_c
/////////////////////////////////////////////////////////////////////////////

inline void Throttler_c::SetDefaultThrottlingPeriodMS ( int tmPeriodMs )
{
	tmThrotleTimeQuantumMs = tmPeriodMs<0 ? tmDefaultThrotleTimeQuantumMs : tmPeriodMs;
}

template<typename FN_AFTER_RESUME>
bool Throttler_c::ThrottleAndProceed ( FN_AFTER_RESUME fnProceeder )
{
	if ( MaybeThrottle () )
	{
		fnProceeder ();
		return true;
	}
	return false;
}


/////////////////////////////////////////////////////////////////////////////
/// ConditionVariableAny_c
/////////////////////////////////////////////////////////////////////////////

template<typename LockType>
void ConditionVariableAny_c::Wait ( LockType& tMutex )
{
	auto* pActiveWorker = Worker();
	// atomically call tMutex.unlock() and block on current worker
	// store this coro in waiting-queue
	sph::Spinlock_lock tLock { m_tWaitQueueSpinlock };
	tMutex.Unlock();
	m_tWaitQueue.SuspendAndWait ( tLock, pActiveWorker );

	// relock external again before returning
	tMutex.Lock();
}

template<typename LockType>
bool ConditionVariableAny_c::WaitUntil ( LockType& tMutex, int64_t iTimestamp )
{
	auto* pActiveWorker = Worker();
	// atomically call tMutex.unlock() and block on current worker
	// store this coro in waiting-queue
	sph::Spinlock_lock tLock { m_tWaitQueueSpinlock };
	tMutex.Unlock();
	bool bResult = m_tWaitQueue.SuspendAndWaitUntil ( tLock, pActiveWorker, iTimestamp );

	// relock external again before returning
	tMutex.Lock();
	return bResult;
}

template<typename LockType>
bool ConditionVariableAny_c::WaitForMs ( LockType& tMutex, int64_t iTimePeriodMS )
{
	return WaitUntil ( tMutex, sphMicroTimer() + iTimePeriodMS*1000 );
}

template<typename LockType, typename PRED>
void ConditionVariableAny_c::Wait ( LockType& tMutex, PRED fnPred )
{
	while ( !fnPred() ) {
		Wait ( tMutex );
	}
}

template<typename LockType, typename PRED>
bool ConditionVariableAny_c::WaitUntil ( LockType& tMutex, PRED fnPred, int64_t iTimestamp )
{
	while ( !fnPred() ) {
		if ( !WaitUntil ( tMutex, iTimestamp ) )
			return fnPred();
	}
	return true;
}

template<typename LockType, typename PRED>
bool ConditionVariableAny_c::WaitForMs ( LockType& tMutex, PRED fnPred, int64_t iTimePeriodMS )
{
	return WaitUntil ( tMutex, std::forward<PRED> ( fnPred ), sphMicroTimer() + iTimePeriodMS * 1000 );
}

/////////////////////////////////////////////////////////////////////////////
/// ConditionVariable_c
/////////////////////////////////////////////////////////////////////////////

template<typename PRED>
void ConditionVariable_c::Wait ( ScopedMutex_t& lt, PRED&& fnPred ) REQUIRES ( lt )
{
	m_tCnd.Wait ( lt, std::forward<PRED> ( fnPred ) );
}

template<typename PRED>
bool ConditionVariable_c::WaitUntil ( ScopedMutex_t& lt, PRED&& fnPred, int64_t iTime ) REQUIRES ( lt )
{
	return m_tCnd.WaitUntil ( lt, std::forward<PRED> ( fnPred ), iTime );
}

template<typename PRED>
bool ConditionVariable_c::WaitForMs ( ScopedMutex_t& lt, PRED&& fnPred, int64_t iPeriodMS ) REQUIRES ( lt )
{
	return m_tCnd.WaitForMs ( lt, std::forward<PRED> ( fnPred ), iPeriodMS );
}

/////////////////////////////////////////////////////////////////////////////
/// Waitable_T
/////////////////////////////////////////////////////////////////////////////

template<typename T>
template<typename... PARAMS>
Waitable_T<T>::Waitable_T ( PARAMS&&... tParams )
	: m_tValue ( std::forward<PARAMS> ( tParams )... )
{}

template<typename T>
void Waitable_T<T>::SetValue ( T tValue )
{
	ScopedMutex_t lk ( m_tMutex );
	m_tValue = tValue;
}

template<typename T>
T Waitable_T<T>::ExchangeValue ( T tNewValue )
{
	ScopedMutex_t lk ( m_tMutex );
	return std::exchange ( m_tValue, tNewValue );
}

template<typename T>
void Waitable_T<T>::SetValueAndNotifyOne ( T tValue )
{
	SetValue ( tValue );
	NotifyOne();
}

template<typename T>
void Waitable_T<T>::SetValueAndNotifyAll ( T tValue )
{
	SetValue ( tValue );
	NotifyAll();
}

template<typename T>
void Waitable_T<T>::UpdateValueAndNotifyOne ( T tValue )
{
	if ( tValue == GetValue() )
		return;
	SetValueAndNotifyOne ( tValue );
}

template<typename T>
void Waitable_T<T>::UpdateValueAndNotifyAll ( T tValue )
{
	if ( tValue == GetValue() )
		return;
	SetValueAndNotifyAll ( tValue );
}

template<typename T>
template<typename MOD>
void Waitable_T<T>::ModifyValue ( MOD&& fnMod )
{
	ScopedMutex_t lk ( m_tMutex );
	fnMod ( m_tValue );
}

template<typename T>
template<typename MOD>
void Waitable_T<T>::ModifyValueAndNotifyOne ( MOD&& fnMod )
{
	ModifyValue ( std::forward<MOD> ( fnMod ) );
	NotifyOne();
}

template<typename T>
template<typename MOD>
void Waitable_T<T>::ModifyValueAndNotifyAll ( MOD&& fnMod )
{
	ModifyValue ( std::forward<MOD> ( fnMod ) );
	NotifyAll();
}

template<typename T>
T Waitable_T<T>::GetValue() const
{
	return m_tValue;
}

template<typename T>
const T& Waitable_T<T>::GetValueRef() const
{
	return m_tValue;
}

template<typename T>
inline void Waitable_T<T>::NotifyOne()
{
	m_tCondVar.NotifyOne();
}

template<typename T>
inline void Waitable_T<T>::NotifyAll()
{
	m_tCondVar.NotifyAll();
}

template<typename T>
void Waitable_T<T>::Wait () const
{
	ScopedMutex_t lk ( m_tMutex );
	m_tCondVar.Wait ( lk );
}

template<typename T>
bool Waitable_T<T>::WaitUntil(int64_t iTime) const
{
	ScopedMutex_t lk ( m_tMutex );
	return m_tCondVar.WaitUntil ( lk, iTime );
}

template<typename T>
bool Waitable_T<T>::WaitForMs(int64_t iPeriodMS) const
{
	ScopedMutex_t lk ( m_tMutex );
	return m_tCondVar.WaitForMs ( lk, iPeriodMS );
}

template<typename T>
template<typename PRED>
T Waitable_T<T>::Wait ( PRED&& fnPred ) const
{
	ScopedMutex_t lk ( m_tMutex );
	m_tCondVar.Wait ( lk, [this, fnPred = std::forward<PRED> ( fnPred )]() { return fnPred ( m_tValue ); } );
	return m_tValue;
}

template<typename T>
template<typename PRED>
T Waitable_T<T>::WaitUntil ( PRED&& fnPred, int64_t iTime ) const
{
	ScopedMutex_t lk ( m_tMutex );
	m_tCondVar.WaitUntil ( lk, [this, fnPred = std::forward<PRED> ( fnPred )]() { return fnPred ( m_tValue ); }, iTime );
	return m_tValue;
}

template<typename T>
template<typename PRED>
T Waitable_T<T>::WaitForMs ( PRED&& fnPred, int64_t iPeriodMs ) const
{
	ScopedMutex_t lk ( m_tMutex );
	m_tCondVar.WaitForMs ( lk, [this, fnPred = std::forward<PRED> ( fnPred )]() { return fnPred ( m_tValue ); }, iPeriodMs );
	return m_tValue;
}

template<typename T>
template<typename PRED>
void Waitable_T<T>::WaitVoid ( PRED&& fnPred ) const
{
	ScopedMutex_t lk ( m_tMutex );
	m_tCondVar.Wait ( lk, std::forward<PRED> ( fnPred ) );
}

template<typename T>
template<typename PRED>
bool Waitable_T<T>::WaitVoidUntil ( PRED&& fnPred, int64_t iTime ) const
{
	ScopedMutex_t lk ( m_tMutex );
	return m_tCondVar.WaitUntil ( lk, std::forward<PRED> ( fnPred ), iTime );
}

template<typename T>
template<typename PRED>
bool Waitable_T<T>::WaitVoidForMs ( PRED&& fnPred, int64_t iPeriodMs ) const
{
	ScopedMutex_t lk ( m_tMutex );
	return m_tCondVar.WaitForMs ( lk, std::forward<PRED> ( fnPred ), iPeriodMs );
}


} // namespace Coro
} // namespace Threads

