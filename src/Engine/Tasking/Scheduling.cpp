#include <Engine/Tasking/Scheduling.h>
#include <Engine/Core/Utility.h>

#include <Concurrent/Scheduler.h>

#include "../private_include/Tasking/SchedulingPrivate.h"

using namespace Concurrent;

namespace Engine
{
	static Scheduler mainScheduler(enumVal(Priority::High));

	bool initScheduling()
	{
		return true;
	}

	void shutdownScheduling()
	{
	}

	void ScheduleTask(std::function<void()>&& func, Priority priority)
	{
		mainScheduler.addTask(std::forward<std::function<void()>>(func), enumVal(priority));
	}

	void ScheduleTask(Task* task, Priority priority)
	{
		mainScheduler.addTask(task, enumVal(priority));
	}
}