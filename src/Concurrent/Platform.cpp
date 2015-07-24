#include "private_include/Platform.h"

#if defined(_WIN32)

#include <Windows.h>
#include <concrt.h>

using namespace std;

namespace Concurrent
{
	struct ThreadSpecs
	{
		void (*func)(void*);
		void* param;
	};

	static DWORD WINAPI sysThreadRunner(LPVOID lpParam)
	{
		ThreadSpecs* specs = static_cast<ThreadSpecs*>(lpParam);
		
		// Copy the thread specs to the stack so the heap space used to
		// pass them into the system thread function can be quickly reclaimed
		void(*func)(void*) = specs->func;
		void* param = specs->param;

		delete specs;

		func(param);

		return 0;
	}

	void sysScheduleFunction(void (*func)(void*), void* param)
	{
		Concurrency::CurrentScheduler::ScheduleTask(func, param);
	}

	void sysRunAsThread(void (*func)(void*), void* param)
	{
		ThreadSpecs* specs = new ThreadSpecs;
		specs->func = func;
		specs->param = param;

		HANDLE winHandle = CreateThread(NULL, NULL, &sysThreadRunner, specs, CREATE_SUSPENDED, NULL);
		ResumeThread(winHandle);
		CloseHandle(winHandle);
	}

	///////////////////

	static DWORD WINAPI sysFunctionalJump(LPVOID lpParam)
	{
		function<void()>* funcPtr = static_cast<function<void()>*>(lpParam);
		(*funcPtr)();

		delete funcPtr;

		return 0;
	}

	void sysRunAsThread(std::function<void()>&& func)
	{
		function<void()>* funcPtr = new function<void()>(forward<function<void()>>(func));

		HANDLE winHandle = CreateThread(NULL, NULL, &sysFunctionalJump, funcPtr, CREATE_SUSPENDED, NULL);
		ResumeThread(winHandle);
		CloseHandle(winHandle);
	}
}

#else
#	error Add platform support for system scheduling functions.
#endif