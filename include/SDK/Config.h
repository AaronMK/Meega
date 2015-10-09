#ifndef _MEEGA_SDK_CONFIG_H_
#define _MEEGA_SDK_CONFIG_H_

#ifndef _WIN32
#	define ENGINE_FUNC_EXPORT extern
#	define ENGINE_DYNAMIC_CLASS
#else
#	ifdef MEEGA_SDK_BUILD
#		define MEEGA_SDK_FUNCTION __declspec(dllexport)
#		define MEEGA_SDK_CLASS __declspec(dllexport)
#	else
#		define MEEGA_SDK_FUNCTION extern
#		define MEEGA_SDK_CLASS __declspec(dllimport)
#	endif
#endif

#endif // _MEEGA_SDK_CONFIG_H_