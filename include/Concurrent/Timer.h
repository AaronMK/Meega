#ifndef _CONCURRENT_TIMER_H_
#define _CONCURRENT_TIMER_H_

#include <Concurrent/Internal/TimerPlatform.h>

#include <functional>

namespace Concurrent
{
	class CONCURRENT_DYNAMIC_CLASS Timer : public TimerPlatform
	{
	public:
		Timer(const Timer&) = delete;
		Timer(Timer&&) = delete;

		Timer(std::function<void(void)>&& func, unsigned int milliseconds);
		Timer();

		virtual ~Timer();

		void start(std::function<void(void)>&& func, unsigned int milliseconds);
		void start();
		
		void oneShot(std::function<void(void)>&& func, unsigned int milliseconds);
		void oneShot();

		void stop();
		void clear();
	};
}

#endif // _CONCURRENT_TIMER_H_