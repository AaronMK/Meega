#ifndef _ENGINE_TIMING_H_
#define _ENGINE_TIMING_H_

#include "../Engine.h"

#include <cstdint>

namespace Engine
{
	/*
	 * Global timing functionality for the engine.  All metrics represent the state quaried
	 * when update() is called to keep consistency in frames.
	 */
	class ENGINE_DYNAMIC_CLASS Timing
	{
	public:

		/*
		 * Initializes timing functions of the engine and zeroes counters.
		 */
		static void initialize();

		/*
		 * Updates timing metrics.
		 */
		static void update();
		
		/**
		 * Returns a time in milliseconds in realworld time since the Engine started.
		 * This is not vulnerble to fluctuations in Engine-time. 
		 */
		static uint64_t WorldMSecs();
		
		/**
		 * Returns a time in milliseconds since the engine has started.  This reflects
		 * Engine-time.
		 */
		static uint64_t EngineMSecs();

		/*
		 * Gets the milliseconds in Engine-time that passed between the previous update() call
		 * and the one before that.
		 */
		static uint32_t updateDeltaMSecs();

		/*
		* Gets the seconds in Engine-time that passed between the previous update() call
		* and the one before that.
		*/
		static float updateDeltaSeconds();
	};
}

#endif // _ENGINE_TIMING_H_