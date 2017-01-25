#ifndef _ENGINE_TIMING_H_
#define _ENGINE_TIMING_H_

#include "../Engine.h"

#include <chrono>

namespace Engine
{
	/**
	 * @brief
	 *  Global timing functionality for the engine.  All metrics represent the state quaried
	 *  when update() is called to keep consistency in frames.
	 */
	class ENGINE_EXPORT Timing
	{
	public:

		/**
		 * @brief
		 *  Initializes timing functions of the engine and zeroes counters.
		 */
		static void initialize();

		/**
		 * @brief
		 *  Updates timing metrics.
		 */
		static void update();
		
		/**
		 * @brief
		 *  Returns a time in realworld time since the Engine started.
		 *  This is not vulnerble to fluctuations in Engine-time. 
		 */
		static std::chrono::high_resolution_clock::duration world();
		
		/**
		 * @brief
		 *  Returns a time since the engine has started.  This reflects Engine-time.
		 */
		static std::chrono::high_resolution_clock::duration engine();

		/**
		 * @brief
		 *  Gets Engine-time that passed between the previous update() call
		 *  and the one before that.
		 */
		static std::chrono::high_resolution_clock::duration updateDelta();
	};
}

#endif // _ENGINE_TIMING_H_