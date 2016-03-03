#ifndef _CONCURRENT_QUEUE_PLATFORM_H_
#define _CONCURRENT_QUEUE_PLATFORM_H_

#include <Concurrent/Config.h>

#ifdef _WIN32

#include <concurrent_queue.h>

namespace Concurrent
{
	/**
	 * @internal
	 */
	template<typename T>
	class QueuePlatform
	{
	protected:
		concurrency::concurrent_queue<T> mSysQueue;
	};
}

#endif

#endif // _CONCURRENT_QUEUE_PLATFORM_H_