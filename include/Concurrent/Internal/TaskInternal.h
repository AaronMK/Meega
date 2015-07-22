#ifndef _CONCURRENT_TASK_INTERNAL_H_
#define _CONCURRENT_TASK_INTERNAL_H_

#include <Concurrent/Condition.h>
#include <Concurrent/Reference.h>

#include <Concurrent/Internal/SchedulerInternal.h>

#include <atomic>

namespace Concurrent
{
	class CONCURRENT_DYNAMIC_CLASS TaskInternal
	{
		friend class Task;
		friend class Scheduler;
		friend class SchedulerInternal;

	private:
		TaskInternal();
		virtual ~TaskInternal();

		void schedulerAcquire();
		void schedulerRelease();

		std::atomic<int> mDependentCount;
		Condition mFinishedHandle;

		Scheduler* mScheduler;
		Task* mParent;

		void doRun();
	};
}

#endif // _CONCURRENT_TASK_INTERNAL_H_