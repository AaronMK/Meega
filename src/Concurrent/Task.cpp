#include <Concurrent/Task.h>

#include <Concurrent/Scheduler.h>
#include <Concurrent/ThreadLocalPtr.h>

#include "private_include/Platform.h"

#include <cassert>

namespace Concurrent
{
	static ThreadLocalPtr<Task> runningTask;

	/////////////////////////////////////

	TaskInternal::TaskInternal()
	{
	}

	TaskInternal::~TaskInternal()
	{
	}

	void TaskInternal::doRun()
	{
		Task* task = dynamic_cast<Task*>(this);

		runningTask.set(task);
		task->main();
		runningTask.set(nullptr);

		Task* shutdownTask = task;
		
		while ( nullptr != shutdownTask )
		{
			Task* nextShutdown = shutdownTask->mParent;
			
			if (0 == --shutdownTask->mDependentCount)
			{
				shutdownTask->mParent = nullptr;
				shutdownTask->mFinishedHandle.trigger();
			}	
			
			shutdownTask = nextShutdown;
		}
	}

	///////////////////////////////////////

	Task::Task()
	{
		mFinishedHandle.trigger();
		mDependentCount.store(0);
		mParent = nullptr;
	}

	Task::~Task()
	{
	}

	bool Task::isRunning()
	{
		return !mFinishedHandle.isTriggered();
	}

	void Task::wait()
	{
		mFinishedHandle.wait();
	}

	Task* Task::current()
	{
		return runningTask.get();
	}

	bool Task::subTask(Task* childTask)
	{
		assert(current() == this && this != childTask);

		childTask->mParent = this;

		SchedulerInternal::TaskRecord record;
		record.func = std::bind(&TaskInternal::doRun, childTask);

		Scheduler* currentScheduler = Scheduler::current();

		currentScheduler->mInternal->highPriorityQueue.push(record);
		sysScheduleFunction(&SchedulerInternal::taskRunner, currentScheduler);

		return true;
	}

#ifdef _WIN32
	void Task::yield()
	{
		Concurrency::Context::CurrentContext()->Yield();
	}
#else
#	error Need to implement Task::yield() on current platform.
#endif

}
