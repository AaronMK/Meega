#ifndef _CONCURRENT_SCHEDULER_H_
#define _CONCURRENT_SCHEDULER_H_

#include "Config.h"
#include "Reference.h"

#include "Internal/SchedulerInternal.h"

namespace Concurrent
{
	/**
	 * @brief
	 *  An object for scheduling and prioritizing tasks.
	 * 
	 *  A Scheduler runs tasks making sure that any tasks that have been added with a higher
	 *  priority will be sent to the system threadpool for execution before those with lower
	 *  priorities.
	 * 
	 *  There can be multiple schedulers, and internally the system will round-robin all 
	 *  the active schedulers, pulling the highest priority task from eachin turn.  Any
	 *  tasks passed with the same priority will be run in the order they are submitted.
	 */
	class CONCURRENT_DYNAMIC_CLASS Scheduler
	{
		friend class SchedulerInternal;
		friend class Task;

	public:
		Scheduler(const Scheduler&) = delete;
		Scheduler& operator=(const Scheduler&) = delete;

		/**
		 * Creates a scheduler with the passed value as the highest priority level.
		 * Valid priorities will be in the range of [0, maxPriority].  Passing a value
		 * or zero or less will create a scheduler that simply submits tasks to the
		 * system thread pool in the order received.
		 */
		Scheduler(int maxPriority);
		
		/**
		 * Move constructor.
		 *
		 * Management of tasks passed to other will move to this.
		 */
		Scheduler(Scheduler&& other);

		/**
		 * Destructor of the scheduler object.  Any tasks still remaing in the
		 * scheduler will still be sent to the system threadpool in the proper order
		 * even after the scheduler object is gone.
		 */
		virtual ~Scheduler();

		/**
		 * Adds a function for scheduling.  If the passed priority is
		 * greater than that of the scheduler, it will be clamped.
		 */
		void addTask(std::function<void()>&& func, int priority);

		/**
		 * Adds a task for scheduling.  If the passed priority is
		 * greater than that of the scheduler, it will be clamped.
		 */
		void addTask(Task* task, int priority);

		/**
		 * Move assignment.
		 *
		 * Management of tasks passed to other will move to the l-value.
		 */
		Scheduler& operator=(Scheduler&& other);

		/**
		 * Gets a default scheduler with a single priority.  This is also the scheduler
		 * that is used when a task run as a thread creates a subtask.
		 */
		static Scheduler* default();

		/**
		 * Runs a task in its own thread.
		 */
		static void runAsThread(Task* task);

		/**
		 * Runs a task inline in the current thread, and does not return until the
		 * task and any subtasks it schedules have been completed.
		 */
		static void runInline(Task* task);

		template<typename T>
		static void forEach(std::vector<T> vec, const std::function<void(T*)>& func);

	private:
		Reference<SchedulerInternal> mInternal;
	};

	template<typename T>
	static void Scheduler::forEach(std::vector<T> vec, const std::function<void(T*)>& func)
	{
		unsigned int taskElements = std::thread::hardware_concurrency()/vec.size();


	}
}

#endif // _CONCURRENT_SCHEDULER_H_