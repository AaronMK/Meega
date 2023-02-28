#include <Engine/Engine.h>

#include <StdExt/Concurrent/FunctionTask.h>

#include <Engine/Tasking/Scheduling.h>
#include <Engine/Timing/Timing.h>

#include <GPU/OpenGL/OpenGL.h>

#include "private_include/Tasking/PipelinePrivate.h"

using namespace StdExt::Concurrent;

namespace Engine
{
	bool initialize()
	{
		if (false == checkRuntimeConfig())
			return false;

		Timing::initialize();
		return (OpenGL::initialize() && initPipeline());
	}

	void shutdown()
	{
		shutdownPipeline();
		OpenGL::shutdown();
	}
}