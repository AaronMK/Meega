#include <GPU/Config.h>

#if !defined(_GPU_OPEN_GL_H_) && defined(GPU_SUPPORT_OPEN_GL)
#define _GPU_OPEN_GL_H_

#include "Common.h"

#include <string>

namespace OpenGL
{
	/**
	 * Performs OpenGL initialization.  This must be called before any use of OpenGL functionality.
	 */
	GPU_DYNAMIC_FUNC_EXPORT bool initialize();

	/**
	 * Peforms shutdown of OpenGL and frees related resources.
	 */
	GPU_DYNAMIC_FUNC_EXPORT bool shutdown();

	/**
	 * Gets the maximum version of the OpenGL API that is supported on the host system.
	 */
	GPU_DYNAMIC_FUNC_EXPORT void maxGLVersion(int* outMajor, int *outMinor);
	
	/**
	 * Gets the vender of the default renderer.
	 */
	GPU_DYNAMIC_FUNC_EXPORT const std::string& getGLVendorString();

	/**
	 * Gets the renderer string of the default OpenGL implmentation.
	 */
	GPU_DYNAMIC_FUNC_EXPORT const std::string& getGLRendererString();

	/**
	 * Gets a string description of the last OpenGL error.
	 */
	GPU_DYNAMIC_FUNC_EXPORT const char* getLastError();
}

#endif // _GPU_OPEN_GL_H_