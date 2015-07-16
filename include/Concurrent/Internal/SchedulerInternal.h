#ifndef _CONCURRENT_SCHEDULER_INTERNAL_H_
#define _CONCURRENT_SCHEDULER_INTERNAL_H_

#include <Concurrent/RWLock.h>
#include <Concurrent/Queue.h>

#include <atomic>
#include <vector>
#include <functional>

namespace Concurrent
{
	class Task;

	class SchedulerInternal
	{
		friend class Task;
		friend class Scheduler;
	public:

		struct TaskRecord
		{
			std::function<void()> func;
			Reference<SchedulerInternal> ref;

			TaskRecord()
			{
			}

			TaskRecord(TaskRecord&& other)
			{
				ref = other.ref;
				func = std::move(other.func);
			}

			TaskRecord& operator=(TaskRecord&& other)
			{
				ref = other.ref;
				func = std::move(other.func);

				return *this;
			}
		};

		SchedulerInternal(size_t maxPriority);
		virtual ~SchedulerInternal();

		static void taskRunner(void* scheduler);

		Queue<TaskRecord> highPriorityQueue;
		std::vector< Queue<TaskRecord> > mTaskQueues;
	};
}

#endif // _CONCURRENT_SCHEDULER_INTERNAL_H_