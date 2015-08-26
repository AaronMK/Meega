#ifndef _ENGINE_CONFIG_H_
#define _ENGINE_CONFIG_H_

/** \def ENGINE_API_OPEN_GL
 * Define to have the engine compiled for use with the OpenGL API.
 */
#define ENGINE_API_OPEN_GL

/** \def ENGINE_API_DIRECT_X
 * Define to have the engine compiled for use with the DirectX.
 */
// #define ENGINE_API_DIRECT_X

/** \def ENGINE_DEVEOPMENT_SUPPORT
 * Define this to put development support into the engine.  This will enable
 * a great deal of functionality to assist in debugging of applications at a
 * noticeable cost in terms of memory, speed, and code bloat.
 */

////////////////////////////////////////////////////////////////////////////
//////// Configuration End - Don't modify anything below this line. ////////
////////////////////////////////////////////////////////////////////////////

#define ENGINE_VERSION_MAJOR 1
#define ENGINE_VERSION_MINOR 0
#define ENGINE_VERSION_PATCH 0

// Configure 32 or 64 bit defines
#if defined(_M_AMD64)
#	define ENGINE_64_BIT
#else
#	define ENGINE_32_BIT
#endif

#if defined(_WIN32)
#	define ENGINE_PLATORM_WINDOWS

#	ifndef NOMINMAX
#		define NOMINMAX
#		undef min
#		undef max
#	endif
#endif

#if !defined(ENGINE_DYNAMIC) || !defined(_WIN32)
#	define ENGINE_FUNC_EXPORT extern
#	define ENGINE_DYNAMIC_CLASS
#else
#	ifdef ENGINE_BUILD
#		define ENGINE_DATA_EXPORT __declspec(dllexport)
#		define ENGINE_FUNC_EXPORT __declspec(dllexport)
#		define ENGINE_DYNAMIC_CLASS __declspec(dllexport)
#	else
#		define ENGINE_DATA_EXPORT __declspec(dllimport)
#		define ENGINE_FUNC_EXPORT extern
#		define ENGINE_DYNAMIC_CLASS __declspec(dllimport)
#	endif
#endif

namespace Engine
{
	ENGINE_FUNC_EXPORT bool DevelopmentSupport();
	ENGINE_FUNC_EXPORT bool DynamicLibrary();

	static bool checkRuntimeConfig()
	{
		bool ret = true;

#		ifdef	ENGINE_DEVEOPMENT_SUPPORT
			ret &= DevelopmentSupport();
#		else
			ret &= !DevelopmentSupport();
#		endif

#		ifdef	ENGINE_DYNAMIC
			ret &= DynamicLibrary();
#		else
			ret &= !DynamicLibrary();
#		endif

		return ret;
	}
}

#endif // _ENGINE_CONFIG_H_