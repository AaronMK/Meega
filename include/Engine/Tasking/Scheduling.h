#ifndef _ENGINE_SCHEDULING_H_
#define _ENGINE_SCHEDULING_H_

#include "../Config.h"

#include <Concurrent/Task.h>

#include <functional>

namespace Engine
{
	enum class Priority : int
	{
		Background,
		Regular,
		High
	};

	ENGINE_EXPORT void ScheduleTask(std::function<void()>&& func, Priority priority);
	ENGINE_EXPORT void ScheduleTask(Concurrent::Task* task, Priority priority);
}

#endif // _ENGINE_SCHEDULING_H_