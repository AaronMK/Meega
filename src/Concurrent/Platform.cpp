#include "private_include/Platform.h"

#if defined(_WIN32)

#include <Windows.h>
#include <concrt.h>

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
}

#else
#	error Add platform support for system scheduling functions.
#endif