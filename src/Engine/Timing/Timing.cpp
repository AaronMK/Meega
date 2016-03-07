#include <Engine/Timing/Timing.h>

#include <limits>

#include <Windows.h>
#include <mmsystem.h>

#include <algorithm>
#include <chrono>

using namespace std::chrono;

namespace Engine
{
	/**
	 * @internal
	 *
	 * @brief
	 *  Max amount of time that is allowed to be considered passed between updates.
	 *  This makes break points and pauses practical.
	 */
	static const high_resolution_clock::duration MAX_ENGINE_DELTA
		= duration_cast<high_resolution_clock::duration>(milliseconds(33));

	/**
	 * @internal
	 *
	 * @brief
	 *  Amount of time since the last call to update().
	 */
	static high_resolution_clock::duration engineTimeDelta;

	/**
	 * @internal
	 *
	 * @brief
	 *  Amount of engine time since timing was initialized.
	 */
	static high_resolution_clock::duration engineTime;

	/**
	 * @internal
	 *
	 * @brief
	 *  Amount of world time since the Engine started.
	 */
	static high_resolution_clock::duration worldTime;

	/**
	 * @internal
	 *
	 * @brief
	 *  WorldTime of last update based on the system clock.
	 */
	static time_point<high_resolution_clock> lastUpdate;

	////////////////////////////////////////////////

	void Timing::initialize()
	{
		engineTime = high_resolution_clock::duration(0);
		worldTime = high_resolution_clock::duration(0);
		engineTimeDelta = high_resolution_clock::duration(0);
		lastUpdate = high_resolution_clock::now();
	}

	void Timing::update()
	{
		time_point<high_resolution_clock> currentUpdate = high_resolution_clock::now();
		high_resolution_clock::duration worldTimeDelta = currentUpdate - lastUpdate;

		engineTimeDelta = std::min(worldTimeDelta, MAX_ENGINE_DELTA);

		worldTime += worldTimeDelta;
		engineTime += engineTimeDelta;

		lastUpdate = currentUpdate;
	}

	high_resolution_clock::duration Timing::world()
	{
		return worldTime;
	}

	high_resolution_clock::duration Timing::engine()
	{
		return engineTime;
	}

	high_resolution_clock::duration Timing::updateDelta()
	{
		return engineTimeDelta;
	}
}