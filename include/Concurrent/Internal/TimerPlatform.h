#ifndef _CONCURRENT_TIMER_PLATFORM_H_
#define _CONCURRENT_TIMER_PLATFORM_H_

#include "../Config.h"

#ifdef _WIN32

#include <agents.h>

namespace Concurrent
{
	/**
	 * @internal
	 */
	class CONCURRENT_DYNAMIC_CLASS TimerPlatform
	{
	protected:
		TimerPlatform();
		virtual ~TimerPlatform();

		typedef Concurrency::timer<TimerPlatform*> sysTimer_t;
		static const size_t sysTimerSize = sizeof(sysTimer_t);

		sysTimer_t* mTimer;
		unsigned char mTimerMemory[sysTimerSize];

		bool mRepeat;
		std::function<void(void)> mHandler;
		unsigned int mInterval;

		void constructTimer();
		void clearTimer();
	};
}

#endif 

#endif // _WIN32