#include <Engine/Runtime.h>

#if defined(ENGINE_USE_API_OPEN_GL)

#include <GPU/GL/OpenGL.h>

namespace Engine
{	
	GraphicsApi Runtime::graphicsApi()
	{
		return GRAPHICS_API_OPEN_GL;
	}

	bool Runtime::maxOpenGLVersion(int* major, int* minor)
	{
		OpenGL::maxGLVersion(major, minor);
		return true;
	}

	bool Runtime::maxDirectXVersion(int* major, int* minor)
	{
		return false;
	}
}

#endif // defined(USE_ENGINE_USE_API_OPEN_GL)

#if defined(ENGINE_USE_API_DIRECT_X)

namespace Engine
{	
	GraphicsApi Runtime::graphicsApi()
	{
		return GRAPHICS_API_DIRECT_X;
	}

	bool Runtime::maxOpenGLVersion(int* major, int* minor)
	{
		return false;
	}

	bool Runtime::maxDirectXVersion(int* major, int* minor)
	{
		assert(false); // Need to implement.
	}
}

#endif // defined(ENGINE_USE_API_DIRECT_X)