#include <GPU/Config.h>

#if !defined(_GPU_OPEN_GL_FORMAT_H_) && defined(GPU_SUPPORT_OPEN_GL)
#define _GPU_OPEN_GL_FORMAT_H_

#include "../OpenGL/Common.h"

namespace OpenGL
{
	/**
	 * @brief
	 *  Applicable to OpenGL 3.1 and above.  Determines deprecation behaviour.
	 */
	enum class Profile
	{
		/**
		 * @brief
		 *  Deprecated functions are not available, only core functionality for the specified version.
		 */
		CORE,

		/**
		 * @brief
		 *  Deprecated functions are available.
		 */
		COMPATIBILITY
	};

	struct GPU_DYNAMIC_CLASS Format
	{	
		Format();

		unsigned int versionMajor;
		unsigned int versionMinor;
		Profile versionProfile;
		bool debug;
	};
}

#endif // _GPU_OPEN_GL_FORMAT_H_