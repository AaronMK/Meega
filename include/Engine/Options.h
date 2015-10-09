#ifndef _ENGINE_OPTIONS_H_
#define _ENGINE_OPTIONS_H_

#include "Core/Types.h"

#include <GPU/RenderTarget.h>

namespace Engine
{
	class InterfaceHooks;

	/**
	 * Setting for VSync.
	 */
	enum class VSync
	{
		/**
		 * Platform determines the best option for vsync.
		 */
		AUTO,

		/**
		 * Force screen updates to happen at the time of the swapbuffers call.
		 * This may result in screen tearing.
		 */
		OFF,

		/**
		 * Sychronize buffer swaps with monitor refresh.  This may result in the
		 * graphics pipeline stalling waiting for refresh.
		 */
		ON
	};

	/**
	 * Startup options for the engine.
	 */
	struct ENGINE_DYNAMIC_CLASS Options
	{
		Options();

		/**
		 * Sets the interface hooks as soon as possible to the provided hooks so
		 * initialization messages will be received.
		 */
		InterfaceHooks *interfaceHooks;

		/**
		 * The default target for all drawing done in the render thread.  This must be
		 * avaliable for the duration of when the engine is active.
		 */
		GPU::RenderTarget* mainRenderTarget;

		/**
		 * Set this to force swapping of the frame buffer to monitor vertical synchronization.
		 */
		VSync vSync;

		/**
		 * If true, this enabbles additional debugging functionality of the underlying API.
		 * For builds of the engine with deveoplment support, this will default to true.
		 */
		bool debug;
	};
}

#endif // _ENGINE_OPTIONS_H_