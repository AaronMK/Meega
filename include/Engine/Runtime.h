#ifndef _ENGINE_RUNTIME_H_
#define _ENGINE_RUNTIME_H_

#include "Engine.h"

namespace Engine
{
	enum class GraphicsApi
	{
		Vulkan,
		OpenGL,
		DirectX
	};

	enum Platform
	{
		PLATFORM_WIN32,
		PLATFORM_OSX
	};

	/**
	 * Static functionality used to determine how the engine was compiled and
	 * system capabilities.
	 */
	class ENGINE_DYNAMIC_CLASS Runtime
	{
		/**
		 * Obtains the graphics API against which the library was compiled.
		 */
		static GraphicsApi graphicsApi();

		/**
		 * Obtains the highest version of OpenGL that is supported on the system.
		 * If the Engine was not compiled with OpenGL support, this function
		 * returns false, and nothing is written into major and minor.
		 */
		static bool maxOpenGLVersion(int* major, int* minor);

		/**
		 * Obtains the highest version of DirectX that is supported on the system.
		 * If the Engine was not compiled with DirectX support, this function
		 * returns false, and nothing is written into major and minor.
		 */
		static bool maxDirectXVersion(int* major, int* minor);
	};
}

#endif // 