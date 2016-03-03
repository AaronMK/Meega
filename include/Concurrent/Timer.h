#ifndef _CONCURRENT_TIMER_H_
#define _CONCURRENT_TIMER_H_

#include "Internal/TimerPlatform.h"

#include <functional>

namespace Concurrent
{
	/**
	 * @brief
	 *  A timer object that will call a passed function at set intervals or after a delay.
	 */
	class CONCURRENT_DYNAMIC_CLASS Timer : public TimerPlatform
	{
	public:
		Timer(const Timer&) = delete;
		Timer(Timer&&) = delete;

		/**
		 * Constructs a timer with the passed callback and interval.  start() or oneShot()
		 * must be called to active it.
		 */
		Timer(std::function<void(void)>&& func, unsigned int milliseconds);
		
		/**
		 * Constructs an emprty timer.
		 */
		Timer();

		/**
		 * Destruction of the timer, stopping it if it is running.
		 */
		virtual ~Timer();

		/**
		 * Configures and starts the timer.
		 */
		void start(std::function<void(void)>&& func, unsigned int milliseconds);

		/**
		 * Starts an already configured timer.
		 */
		void start();
		
		/**
		 * Calls the passed function after the passed number of milliseconds.  The timer
		 * will remain configured with the passed parameters.
		 */
		void oneShot(std::function<void(void)>&& func, unsigned int milliseconds);

		/**
		 * Triggers the timer once with parameters already passed in set functions.
		 */
		void oneShot();

		/**
		 * Stops the timer.
		 */
		void stop();

		/**
		 * Clear callback and timing settings.
		 */
		void clear();
	};
}

#endif // _CONCURRENT_TIMER_H_