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
		mFinishedHandle.trigger();
		mDependentCount.store(0);

		mScheduler = nullptr;
		mParent = nullptr;
	}

	TaskInternal::~TaskInternal()
	{
		assert(nullptr == mScheduler && nullptr == mParent);
	}

	void TaskInternal::schedulerAcquire()
	{
		if (1 == ++mDependentCount)
			mFinishedHandle.reset();
	}

	void TaskInternal::schedulerRelease()
	{
		if (0 == --mDependentCount)
		{
			if (mParent)
			{
				mParent->schedulerRelease();
				mParent = nullptr;
			}

			mScheduler = nullptr;

			// This must be last since any task owning code could destroy
			// the task once wait() returns.
			mFinishedHandle.trigger();
		}
	}

	void TaskInternal::doRun()
	{
		Task* task = dynamic_cast<Task*>(this);

		runningTask.set(task);
		task->main();
		runningTask.set(nullptr);

		task->schedulerRelease();
	}

	///////////////////////////////////////

	Task::Task()
	{
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

	bool Task::subTask(std::function<void()>&& func)
	{
		assert(this == current());

		schedulerAcquire();

		SchedulerInternal::TaskRecord record;
		Scheduler* scheduler = (mScheduler) ? mScheduler : Scheduler::default();

		record.func = std::forward<std::function<void()>>(func);
		record.ref = scheduler->mInternal;
		record.parentTask = this;

		scheduler->mInternal->enqueueRecord(std::move(record), -1);

		return true;
	}

	bool Task::subTask(Task* childTask)
	{
		assert(this == current());

		schedulerAcquire();

		SchedulerInternal::TaskRecord record;
		Scheduler* scheduler = (mScheduler) ? mScheduler : Scheduler::default();
		
		childTask->mParent = this;
		childTask->mScheduler = scheduler;

		record.func = std::bind(&TaskInternal::doRun, childTask);
		record.ref = scheduler->mInternal;
		record.parentTask = nullptr;

		scheduler->mInternal->enqueueRecord(std::move(record), -1);

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
