#include <Concurrent/Scheduler.h>

#include <thread>
#include <algorithm>

#include <Concurrent/Task.h>
#include <Concurrent/ReadLocker.h>
#include <Concurrent/WriteLocker.h>
#include <Concurrent/ThreadLocalPtr.h>

#include "private_include/Platform.h"

namespace Concurrent
{
	static void ScheduleTaskRunner(Scheduler* scheduler)
	{
		sysScheduleFunction(&Concurrent::SchedulerInternal::taskRunner, scheduler);
	}

	static void ThreadRunner(void* param)
	{
		Task* task = static_cast<Task*>(param);
		Scheduler::runInline(task);
	}

	static void RunAsThread(Task* task)
	{
		sysRunAsThread(ThreadRunner, task);
	}

	template <typename T>
	static T clamp(T val, T min, T max)
	{
		return std::max<T>(min, std::min<T>(val, max));
	}

	////////////////////////////////////////////////////////////

	static ThreadLocalPtr<Task> runningTask;
	static ThreadLocalPtr<Scheduler> currentScheduler;

	static Scheduler defaultScheduler(0);

	//////////////////////////////

	Scheduler::Scheduler(int maxPriority)
	{
		mInternal = Reference<SchedulerInternal>::create(maxPriority);
	}

	Scheduler::~Scheduler()
	{
	}

	void Scheduler::addTask(TaskFunction_t&& func, int priority)
	{
		priority = clamp<int>(priority, 0, (int)mInternal->mTaskQueues.size() - 1);
		
		SchedulerInternal::TaskRecord record;
		record.func = std::forward<TaskFunction_t>(func);
		record.ref = mInternal;

		mInternal->mTaskQueues[priority].push(std::move(record));
		sysScheduleFunction(&SchedulerInternal::taskRunner, this);
	}

	void Scheduler::addTask(Task* task, int priority)
	{
		assert(0 == task->mDependentCount);

		task->mFinishedHandle.reset();
		task->mDependentCount = 1;

		addTask(std::bind(&TaskInternal::doRun, task), priority);
	}

	Scheduler* Scheduler::default()
	{
		return &defaultScheduler;
	}

	Scheduler* Scheduler::current()
	{
		Scheduler* curr = currentScheduler.get();
		return (nullptr != curr) ? curr : default();
	}

	void Scheduler::runAsThread(Task* task)
	{
		sysRunAsThread(&ThreadRunner, task);
	}

	void Scheduler::runInline(Task* task)
	{
		assert(0 == task->mDependentCount);

		task->mFinishedHandle.reset();
		task->mDependentCount = 1;

		task->doRun();
		task->wait();
	}

	/////////////////////////////////////////////////

	SchedulerInternal::SchedulerInternal(size_t maxPriority)
	{
		mTaskQueues.resize(maxPriority + 1);
	}
	
	SchedulerInternal::~SchedulerInternal()
	{
	}

	void SchedulerInternal::taskRunner(void* data)
	{
		Scheduler* scheduler = static_cast<Scheduler*>(data);
		currentScheduler.set(scheduler);

		SchedulerInternal* schedulerInternal = scheduler->mInternal.get();

		TaskRecord record;

		if (false == schedulerInternal->highPriorityQueue.tryPop(record))
		{
			for (size_t i = schedulerInternal->mTaskQueues.size() - 1;
				i >= 0 && false == schedulerInternal->mTaskQueues[i].tryPop(record); i--)
			{
			}
		}

		record.func();

		currentScheduler.set(nullptr);
	}
}