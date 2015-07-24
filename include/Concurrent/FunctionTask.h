#ifndef _CONCURRENT_FUNCTION_TASK_H_
#define _CONCURRENT_FUNCTION_TASK_H_

#include <Concurrent/Task.h>

#include <functional>

namespace Concurrent
{
	class CONCURRENT_DYNAMIC_CLASS FunctionTask : public Task
	{
	public:
		FunctionTask() = default;
		FunctionTask(std::function<void()>&& func);

		virtual ~FunctionTask();

		void setFunction(std::function<void()>&& func);

		virtual void main() override;

	private:
		std::function<void()> mFunc;
	};
}

#endif // _CONCURRENT_FUNCTION_TASK_H_