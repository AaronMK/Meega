#include <Engine/Timing/Timing.h>

#include <limits>

#ifdef ENGINE_PLATORM_WINDOWS

#include <Windows.h>
#include <mmsystem.h>

#include <algorithm>

#pragma comment(lib, "Winmm.lib")

namespace Engine
{
	/**
	 * Gets the amount of time since the system started in milliseconds.
	 */
	static uint32_t sysGetTime()
	{
		return timeGetTime();
	}
}

#endif // ENGINE_PLATORM_WINDOWS

namespace Engine
{
	/**
	 * Max amount of time that is allowed to be considered passed between updates.
	 * This makes break points and pauses practical.
	 */
	static const uint32_t MAX_ENGINE_DELTA_MS = 33;

	/*
	 * Amount of engine time in milliseconds since timing was initialized.
	 */
	static uint64_t engineTime;

	/*
	 * Amount of time in milliseconds since the last call to update().
	 */
	static uint32_t engineTimeDeltaMs;

	/*
	 * Amount of engine time since timing was initialized.
	 */
	static float engineTimeDeltaSeconds;

	/*
	 * Amount of world time in milliseconds since the Engine started.
	 */
	static uint64_t worldTime;

	/**
	 * WorldTime of last update based on the system clock.
	 */
	static uint32_t lastUpdate;

	////////////////////////////////////////////////

	void Timing::initialize()
	{
		engineTime = 0;
		worldTime = 0;
		engineTimeDeltaMs = 0;
		engineTimeDeltaSeconds = 0.0f;
		lastUpdate = sysGetTime();
	}

	void Timing::update()
	{
		uint32_t worldTimeDelta = 0;
		uint32_t currentUpdate = sysGetTime();

		// rollover should be EXTREMELY rare, but we account for it here.
		if (lastUpdate > currentUpdate)
			worldTimeDelta = (std::numeric_limits<uint32_t>::max() - lastUpdate) + currentUpdate;
		else
			worldTimeDelta = currentUpdate - lastUpdate;

		engineTimeDeltaMs = std::min(worldTimeDelta, MAX_ENGINE_DELTA_MS);
		engineTimeDeltaSeconds = (float)engineTimeDeltaMs / 1000.0f;

		worldTime += (uint64_t)worldTimeDelta;
		engineTime += (uint64_t)engineTimeDeltaMs;

		lastUpdate = currentUpdate;
	}

	uint64_t Timing::WorldMSecs()
	{
		return worldTime;
	}

	uint64_t Timing::EngineMSecs()
	{
		return engineTime;
	}

	uint32_t Timing::updateDeltaMSecs()
	{
		return engineTimeDeltaMs;
	}

	float Timing::updateDeltaSeconds()
	{
		return engineTimeDeltaSeconds;
	}
}