#include <Engine/Tasking/Scheduling.h>

namespace Engine
{
	void ScheduleTask(StdExt::Concurrent::Task* task, Priority priority)
	{
		task->runAsync();
	}
}