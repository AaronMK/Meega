#ifndef _CONCURRENT_MUTEX_PLATFORM_H_
#define _CONCURRENT_MUTEX_PLATFORM_H_

#include <Concurrent/Config.h>

#include <atomic>
#include <concrt.h>

namespace Concurrent
{
#ifdef _WIN32
	class CONCURRENT_DYNAMIC_CLASS MutexPlatform
	{
	public:
		MutexPlatform();
		virtual ~MutexPlatform();

		Concurrency::critical_section cs;
		std::atomic<int> entryCount;
	};
#else
#	error "Concurrent::Mutex not supported on this platform."
#endif
}

#endif // _CONCURRENT_MUTEX_PLATFORM_H_
