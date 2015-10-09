#ifndef _CONCURRENT_TASK_INTERNAL_H_
#define _CONCURRENT_TASK_INTERNAL_H_

#include "../Condition.h"
#include "../Reference.h"

#include "SchedulerInternal.h"

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