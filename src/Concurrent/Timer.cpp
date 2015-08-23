#include <Concurrent/Timer.h>

#ifdef _WIN32

#include <cassert>

using namespace Concurrency;

namespace Concurrent
{
	TimerPlatform::TimerPlatform()
	{

	}

	TimerPlatform::~TimerPlatform()
	{

	}

	void TimerPlatform::constructTimer()
	{
		assert(nullptr == mTimer);

		static call<TimerPlatform*> funcCall([](TimerPlatform* t)
		{
			t->mHandler();
		});

		new (&mTimerMemory[0])sysTimer_t(mInterval, this, &funcCall, mRepeat);
		mTimer = reinterpret_cast<sysTimer_t*>(&mTimerMemory[0]);
	}

	void TimerPlatform::clearTimer()
	{
		if (mTimer)
		{
			mTimer->stop();

			mTimer->~sysTimer_t();
			mTimer = nullptr;
		}
	}

	/////////////////////////////////////////

	Timer::Timer(std::function<void(void)>&& func, unsigned int milliseconds)
		: Timer()
	{
		mTimer = nullptr;

		mInterval = milliseconds;
		mHandler = std::forward<std::function<void(void)>>(func);
	}

	Timer::Timer()
	{
		mRepeat = false;
		mTimer = nullptr;
		mInterval = 0;
	}

	Timer::~Timer()
	{
		clearTimer();
	}

	void Timer::start(std::function<void(void)>&& func, unsigned int milliseconds)
	{
		clearTimer();

		mInterval = milliseconds;
		mHandler = std::forward<std::function<void(void)>>(func);

		start();
	}

	void Timer::start()
	{
		if (mTimer && mRepeat)
		{
			mTimer->start();
		}
		else
		{
			clearTimer();

			mRepeat = true;

			constructTimer();
			mTimer->start();
		}
	}

	void Timer::oneShot(std::function<void(void)>&& func, unsigned int milliseconds)
	{
		clearTimer();

		mInterval = milliseconds;
		mHandler = std::forward<std::function<void(void)>>(func);

		oneShot();
	}

	void Timer::oneShot()
	{
		if (mTimer && !mRepeat)
		{
			mTimer->start();
		}
		else
		{
			clearTimer();

			mRepeat = false;

			constructTimer();
			mTimer->start();
		}
	}

	void Timer::stop()
	{
		if (mTimer)
			mTimer->stop();
	}

	void Timer::clear()
	{
		clearTimer();

		mInterval = 0;
		mHandler = std::function<void()>();
	}
}

#endif // _WIN32