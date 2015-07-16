#ifndef _GPU_H_
#define _GPU_H_

#include <GPU/Config.h>

/**
 * The GPU namespace is a platform abstration layer for common GPU operations and
 * functionality that would otherwise require platform specific code.
 */
namespace GPU
{
	enum class API
	{
		DIRECT_X,
		OPEN_GL
	};

	/**
	 * Returns true if the library was compiled with and the system supports DirectX.
	 */
	GPU_DYNAMIC_FUNC_EXPORT bool supportsDirectX();
	
	/**
	 * Returns true if the library was compiled with and the system supports OpenGL.
	 */
	GPU_DYNAMIC_FUNC_EXPORT bool supportsOpenGL();

	/**
	 * Return true if the library is being used as a dynamic library.
	 */
	GPU_DYNAMIC_FUNC_EXPORT bool isDynamic();
}

#endif // _GPU_H_