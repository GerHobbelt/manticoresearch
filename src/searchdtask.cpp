//
// Copyright (c) 2017-2022, Manticore Software LTD (https://manticoresearch.com)
// Copyright (c) 2001-2016, Andrew Aksyonoff
// Copyright (c) 2008-2016, Sphinx Technologies Inc
// All rights reserved
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License. You should have
// received a copy of the GPL license along with this program; if you
// did not, you can find it at http://www.gnu.org/
//

#include "searchdtask.h"
#include "coroutine.h"
#include "mini_timer.h"

#ifndef VERBOSE_TASKMANAGER
#define VERBOSE_TASKMANAGER 0
#endif

#if VERBOSE_TASKMANAGER
#define LOG_LEVEL_TSK true
#else
#define LOG_LEVEL_TSK false
#endif

#define LOG_COMPONENT_TSKX "X "

#define INFOX LOGMSG ( INFO, TSK, TSKX )
#define DEBUGX LOGMSG ( DEBUG, TSK, TSKX )
#define WARNX LOGMSG ( WARNING, TSK, TSKX )

// Max num of task flavours (we allocate fixed vec of this size)
// since we have only 7 different tasks for now, pool of 32 slots seems to be enough
constexpr int NUM_TASKS = 32;

//////////////////////////////////////////////////////////////////////////
// Tasks (job classes)
//////////////////////////////////////////////////////////////////////////
static TaskManager::TaskInfo_t g_Tasks [ NUM_TASKS ];
static std::atomic<int> g_iTasks {0};

// wrap naked executor into statistic collector
Threads::Handler AttachClass ( TaskID iTask, Threads::Handler&& fnWorker )
{
	return [iTask, fnWorker=std::move(fnWorker)] () {
		Threads::JobTracker_t dTrack;
		auto& tInfo = g_Tasks[iTask];
		INFOX << "Task " << tInfo.m_sName << " started";
		tInfo.m_iCurrentRunners.fetch_add ( 1, std::memory_order_relaxed );
		auto itmStart = sphMicroTimer();
		std::atomic_thread_fence ( std::memory_order_acquire );
		fnWorker();
		std::atomic_thread_fence ( std::memory_order_release );
		auto itmEnd = sphMicroTimer();
		tInfo.m_iCurrentRunners.fetch_sub ( 1, std::memory_order_relaxed );
		tInfo.m_iAllRunners.fetch_sub ( 1, std::memory_order_relaxed );
		tInfo.m_iTotalRun.fetch_add ( 1, std::memory_order_relaxed );
		tInfo.m_iLastFinished.store ( itmEnd, std::memory_order_relaxed );
		tInfo.m_iTotalSpent.fetch_add ( itmEnd - itmStart, std::memory_order_relaxed );
		INFOX << "Task " << tInfo.m_sName << " finished";
	};
}

void TaskManager::StartJob ( TaskID iTask, Threads::Handler fnJob )
{
	assert ( iTask <= g_iTasks.load ( std::memory_order_relaxed ) && iTask >= 0 );
	auto& tInfo = g_Tasks[iTask];
	auto iAllRunners = tInfo.m_iAllRunners.load ( std::memory_order_relaxed );

	if ( sphInterrupted() )
	{
		INFOX << "Drop job (id=" << iTask << " \"" << tInfo.m_sName << "\"), since interrupted";
		tInfo.m_iTotalDropped.fetch_add ( 1, std::memory_order_relaxed );
		return;
	}

	if ( tInfo.m_iMaxRunners > 0 && iAllRunners >= tInfo.m_iMaxRunners )
	{
		INFOX << "Drop job (id=" << iTask << " \"" << tInfo.m_sName << "\"), since " << iAllRunners << " is running/enqueued";
		tInfo.m_iTotalDropped.fetch_add ( 1, std::memory_order_relaxed );
		return;
	}

	INFOX << "StartJob (id=" << iTask << " \"" << tInfo.m_sName << "\")";
	tInfo.m_iAllRunners.fetch_add ( 1, std::memory_order_relaxed );
	Threads::StartJob ( AttachClass ( iTask, std::move ( fnJob ) ) );
}


TaskID TaskManager::RegisterGlobal ( CSphString sName, int iThreads )
{
	auto iTaskID = TaskID ( g_iTasks.fetch_add ( 1, std::memory_order_relaxed ) );
	if ( !iTaskID ) // this is first class; start log timering
		TimePrefixed::TimeStart();

	INFOX << "Task \"" << sName << "\" registered with id=" << iTaskID << ", running max " << iThreads << " jobs a time" << (iThreads?"":" (0=unlimited)");
	auto& dInfo = g_Tasks[iTaskID];
	dInfo.m_sName = std::move ( sName );
	dInfo.m_iMaxRunners = iThreads;
	return iTaskID;
}

// scheduled job - will live in timeout heap and then fire when time is out.
class ScheduledTask_c final: public MiniTimer_c
{
	TaskID m_iTask;
	Threads::Handler m_fnJob;

private:
	void OnTimer() final
	{
		TaskManager::StartJob ( m_iTask, std::move ( m_fnJob ) );
		delete this;
	}

	~ScheduledTask_c() final
	{
		m_szName = nullptr; // signal to not call remove() in MiniTimer_c dtr
	}

	ScheduledTask_c ( TaskID iTask, Threads::Handler fnTask )
		: m_iTask ( iTask )
		, m_fnJob { std::move ( fnTask ) }
	{
		m_szName = g_Tasks[iTask].m_sName.cstr();
	}

public:
	static void EngageJob ( TaskID iTask, int64_t iTimeStampUS, Threads::Handler fnJob )
	{
		assert ( iTimeStampUS > 0 );
		( new ScheduledTask_c { iTask, std::move ( fnJob ) } )->EngageUS ( iTimeStampUS - sphMicroTimer() );
	}
};

void TaskManager::ScheduleJob ( TaskID iTask, int64_t iTimeStampUS, Threads::Handler fnJob )
{
	INFOX << "ScheduleJob (id=" << iTask << ", \"" << g_Tasks[iTask].m_sName << "\", start " << timestamp_t ( iTimeStampUS ) << ")";
	ScheduledTask_c::EngageJob ( iTask, iTimeStampUS, std::move ( fnJob ) );
}

VecTraits_T<TaskManager::TaskInfo_t> TaskManager::GetTaskInfo ()
{
	return { g_Tasks, g_iTasks.load ( std::memory_order_relaxed ) };
}
