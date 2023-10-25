//
// Copyright (c) 2022, Manticore Software LTD (https://manticoresearch.com)
// All rights reserved
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License. You should have
// received a copy of the GPL license along with this program; if you
// did not, you can find it at http://www.gnu.org
//

#include "task_dispatcher.h"
#include "coroutine.h"

#include <atomic>
#include <cassert>

/////////////////////////////////////////////////////////////////////////////
/// trivial concurrent task dispatcher
/////////////////////////////////////////////////////////////////////////////

class ConcurrentTaskDispatcher_c;

class SingleTaskSource_c final : public Dispatcher::TaskSource_i
{
	ConcurrentTaskDispatcher_c& m_tParent;
	const int 					m_iMaxJob;

public:
	SingleTaskSource_c ( ConcurrentTaskDispatcher_c& tParent, int iJobs );
	bool FetchTask ( int& iTask ) final;
};

class ConcurrentTaskDispatcher_c final: public Dispatcher::TaskDispatcher_i
{
	const int 				m_iJobs;
	const int 				m_iConcurrency;
	std::atomic<int32_t>	m_iCurrentJob;

public:
	ConcurrentTaskDispatcher_c ( int iJobs, int iConcurrency );
	int GetConcurrency() const final;
	std::unique_ptr<Dispatcher::TaskSource_i> MakeSource() final;

	int GetNextConcurrentTask();
};

SingleTaskSource_c::SingleTaskSource_c ( ConcurrentTaskDispatcher_c& tParent, int iJobs )
	: m_tParent ( tParent )
	, m_iMaxJob ( iJobs - 1 )
{}

bool SingleTaskSource_c::FetchTask ( int& iTask )
{
	if ( iTask>=0 )
		return true; // previous value wasn't yet consumed

	auto iNextTask = m_tParent.GetNextConcurrentTask();
	if ( iNextTask < 0 )
		return false;
	iTask = m_iMaxJob - iNextTask;
	return true;
}

ConcurrentTaskDispatcher_c::ConcurrentTaskDispatcher_c ( int iJobs, int iConcurrency )
	: m_iJobs ( iJobs )
	, m_iConcurrency ( iConcurrency ? iConcurrency : Threads::NThreads() )
	, m_iCurrentJob { iJobs - 1 }
{}

int ConcurrentTaskDispatcher_c::GetConcurrency() const
{
	return m_iConcurrency;
}

std::unique_ptr<Dispatcher::TaskSource_i> ConcurrentTaskDispatcher_c::MakeSource()
{
	return std::make_unique<SingleTaskSource_c> ( *this, m_iJobs );
}

int ConcurrentTaskDispatcher_c::GetNextConcurrentTask()
{
	return m_iCurrentJob.fetch_sub ( 1, std::memory_order_relaxed );
}

/////////////////////////////////////////////////////////////////////////////
/// round-robin task dispatcher
/////////////////////////////////////////////////////////////////////////////

class RRTaskSource_c final: public Dispatcher::TaskSource_i
{
	const int m_iJobs;
	const int m_iBatch;
	const int m_iStride;
	const int m_iOffset;
	const bool m_bIdle;

	int m_iMySerie = 0;
	int m_iJobInSerie = 0;

public:
	RRTaskSource_c ( int iJobs, int iFiber, int iBatch, int iFibers );
	bool FetchTask ( int& iTask ) final;
};

RRTaskSource_c::RRTaskSource_c ( int iJobs, int iFiber, int iBatch, int iFibers )
	: m_iJobs ( iJobs )
	, m_iBatch ( iBatch )
	, m_iStride ( iFibers * iBatch )
	, m_iOffset ( iFiber * iBatch )
	, m_bIdle ( iFiber >= iFibers )
{}

bool RRTaskSource_c::FetchTask ( int& iTask )
{
	if ( iTask >= 0 )
		return true; // previous value wasn't yet consumed

	if ( m_bIdle )
		return false;

	auto iJob = m_iMySerie * m_iStride + m_iOffset + m_iJobInSerie;

	if ( iJob >= m_iJobs )
		return false;

	iTask = iJob;

	++m_iJobInSerie;
	if ( m_iJobInSerie >= m_iBatch )
	{
		m_iJobInSerie = 0;
		++m_iMySerie;
	}
	return true;
}

class NullTaskSource_c final: public Dispatcher::TaskSource_i
{
public:
	bool FetchTask ( int& iTask ) final;
};

bool NullTaskSource_c::FetchTask ( int& iTask )
{
	return iTask >= 0;
}

class RRTaskDispatcher_c final: public Dispatcher::TaskDispatcher_i
{
	const int m_iJobs;
	const int m_iConcurrency;
	const int m_iBatch;

	std::atomic<int32_t> m_iNextFiber {0};

public:
	RRTaskDispatcher_c ( int iJobs, int iConcurrency, int iBatch );
	int GetConcurrency() const final;
	std::unique_ptr<Dispatcher::TaskSource_i> MakeSource() final;
};


RRTaskDispatcher_c::RRTaskDispatcher_c ( int iJobs, int iConcurrency, int iBatch )
	: m_iJobs ( iJobs )
	, m_iConcurrency ( iConcurrency ? iConcurrency : Threads::NThreads() )
	, m_iBatch ( iBatch )
{}

int RRTaskDispatcher_c::GetConcurrency() const
{
	return m_iConcurrency;
}

std::unique_ptr<Dispatcher::TaskSource_i> RRTaskDispatcher_c::MakeSource()
{
	int iFiber = m_iNextFiber.fetch_add ( 1, std::memory_order_relaxed );
	if ( iFiber < m_iConcurrency )
		return std::make_unique<RRTaskSource_c> ( m_iJobs, iFiber, m_iBatch, m_iConcurrency );
	return std::make_unique<NullTaskSource_c> ();
}

namespace Dispatcher {
std::unique_ptr<TaskDispatcher_i> MakeTrivial ( int iJobs, int iConcurrency )
{
	return std::make_unique<ConcurrentTaskDispatcher_c> ( iJobs, iConcurrency );
}

std::unique_ptr<TaskDispatcher_i> MakeRoundRobin ( int iJobs, int iConcurrency, int iBatch )
{
	return std::make_unique<RRTaskDispatcher_c> ( iJobs, iConcurrency, iBatch );
}

std::unique_ptr<Dispatcher::TaskDispatcher_i> Make ( int iJobs, int iDefaultConcurrency, Dispatcher::Template_t tWhat )
{
	if ( tWhat.batch )
		return MakeRoundRobin(iJobs, tWhat.concurrency ? tWhat.concurrency : iDefaultConcurrency, tWhat.batch );
	return MakeTrivial ( iJobs, tWhat.concurrency ? tWhat.concurrency : iDefaultConcurrency );
}

Template_t ParseTemplate ( Str_t sTemplate )
{
	StrtVec_t dStr;
	sph::Split ( dStr, sTemplate.first, sTemplate.second, "/" );
	dStr.for_each ( [] ( auto& tVal ) { tVal = sph::Trim ( tVal ); } );
	while ( dStr.GetLength()<2 )
		dStr.Add ( dEmptyStr );

	auto fnParseValue = [] ( Str_t tVal ) -> int
	{
		if ( IsEmpty ( tVal ) )
			return 0;
		if ( tVal.second == 1 && ( *tVal.first == '0' || *tVal.first == '*' ) )
			return 0;
		return atoi ( CSphString ( tVal ).cstr() );
	};
	assert ( dStr.GetLength() >= 2 );
	return { fnParseValue ( dStr[0] ), fnParseValue ( dStr[1] ) };
}

Template_t ParseTemplate ( const char* szTemplate )
{
	return ParseTemplate ( FromSz ( szTemplate ) );
}

std::pair<Template_t, Template_t> ParseTemplates ( Str_t sTemplates )
{
	sTemplates = sph::Trim ( sTemplates, '\'' ); // unquote, if necessary.
	StrtVec_t dStr;
	sph::Split ( dStr, sTemplates.first, sTemplates.second, "+" );
	while ( dStr.GetLength() < 2 )
		dStr.Add ( dEmptyStr );
	assert ( dStr.GetLength() >= 2 );
	return { ParseTemplate ( dStr[0] ), ParseTemplate ( dStr[1] ) };
}

std::pair<Template_t, Template_t> ParseTemplates ( const char* szTemplates )
{
	return ParseTemplates ( FromSz ( szTemplates ) );
}

namespace {
	std::pair<Template_t, Template_t> g_GlobalDispatcherTemplates = ParseTemplates ( getenv ( "MANTICORE_THREADS_EX" ) );
}

void SetGlobalDispatchers ( const char* szTemplates )
{
	g_GlobalDispatcherTemplates = ParseTemplates ( szTemplates );
}

// return stored global dispatchers
Template_t GetGlobalBaseDispatcherTemplate()
{
	return g_GlobalDispatcherTemplates.first;
}

Template_t GetGlobalPseudoShardingDispatcherTemplate()
{
	return g_GlobalDispatcherTemplates.second;
}

void Unify ( Template_t& tBase, const Template_t tNew )
{
	if ( tNew.concurrency )
		tBase.concurrency = tNew.concurrency;

	if ( tNew.batch )
		tBase.batch = tNew.batch;
}

} // namespace Dispatcher
