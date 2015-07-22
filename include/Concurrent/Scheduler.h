#ifndef _CONCURRENT_SCHEDULER_H_
#define _CONCURRENT_SCHEDULER_H_

#include <Concurrent/Config.h>
#include <Concurrent/Reference.h>

#include <Concurrent/Internal/SchedulerInternal.h>

namespace Concurrent
{
	class CONCURRENT_DYNAMIC_CLASS Scheduler
	{
		friend class SchedulerInternal;
		friend class Task;

	public:
		Scheduler(int maxPriority);
		virtual ~Scheduler();

		void addTask(std::function<void()>&& func, int priority);
		void addTask(Task* task, int priority);

		static Scheduler* default();

		static void runAsThread(Task* task);
		static void runInline(Task* task);

	private:
		Reference<SchedulerInternal> mInternal;
	};
}

#endif // _CONCURRENT_SCHEDULER_H_