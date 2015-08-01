#ifndef _ENGINE_PIPELINE_PRIVATE_H_
#define _ENGINE_PIPELINE_PRIVATE_H_

#include <Engine/Config.h>

namespace Engine
{
	class GpuPipeline;

	extern bool initPipeline();
	extern void shutdownPipeline();

	/**
	 * Returns a non-null pointer if the current code is running inside of the two fixed
	 * GpuPipelines of the Engine.
	 *
	 * @internal
	 */
	extern GpuPipeline* currentPipeline();
}

#endif // _ENGINE_PIPELINE_PRIVATE_H_