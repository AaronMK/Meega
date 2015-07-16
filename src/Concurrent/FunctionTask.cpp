#include <Concurrent/FunctionTask.h>

namespace Concurrent
{
	FunctionTask::FunctionTask(const taskfunc &func)
		: mFunc(func)
	{
	}

	FunctionTask::FunctionTask(taskfunc&& func)
		: mFunc(std::forward<taskfunc>(func))
	{

	}

	FunctionTask::~FunctionTask()
	{
	}

	void FunctionTask::setFunction(const taskfunc &func)
	{
		setFunction(taskfunc(func));
	}

	void FunctionTask::setFunction(taskfunc&& func)
	{
		assert(false == Task::isRunning());
		mFunc = std::forward<taskfunc>(func);
	}

	void FunctionTask::main()
	{
		mFunc();
	}
}