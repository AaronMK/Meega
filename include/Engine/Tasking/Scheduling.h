#ifndef _ENGINE_SCHEDULING_H_
#define _ENGINE_SCHEDULING_H_

#include "../Config.h"

#include <StdExt/Concurrent/Task.h>

#include <functional>

namespace Engine
{
	enum class Priority : int
	{
		Background,
		Regular,
		High
	};

	ENGINE_EXPORT void ScheduleTask(StdExt::Concurrent::Task* task, Priority priority);
}

#endif // _ENGINE_SCHEDULING_H_