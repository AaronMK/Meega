#ifndef _CONCURRENT_FUNCTION_TASK_H_
#define _CONCURRENT_FUNCTION_TASK_H_

#include <Concurrent/Task.h>

#include <functional>

namespace Concurrent
{
	class CONCURRENT_DYNAMIC_CLASS FunctionTask : public Task
	{
	public:
		typedef std::function<void()> taskfunc;
		
		FunctionTask() = default;

		FunctionTask(const taskfunc &func);
		FunctionTask(taskfunc&& func);

		virtual ~FunctionTask();

		void setFunction(const taskfunc &func);
		void setFunction(taskfunc&& func);

		virtual void main() override;

	private:
		taskfunc mFunc;
	};
}

#endif // _CONCURRENT_FUNCTION_TASK_H_