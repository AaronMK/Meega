#ifndef _APPS_COMMON_CONFIG_H_
#define _APPS_COMMON_CONFIG_H_

/////////////////////////////////////////

#if defined(_WIN32)
#	if defined(_DEBUG)
#		pragma comment(lib, "Qt6Cored.lib")
#	else
#		pragma comment(lib, "Qt6Core.lib")
#	endif
#endif

#if !defined(APPS_COMMON_DYNAMIC) || !defined(_WIN32)
#	define APPS_COMMON_FUNC_EXPORT extern
#	define APPS_COMMON_DYNAMIC_CLASS
#else
#	ifdef APPS_COMMON_BUILD
#		define APPS_COMMON_FUNC_EXPORT __declspec(dllexport)
#		define APPS_COMMON_DYNAMIC_CLASS __declspec(dllexport)
#	else
#		define APPS_COMMON_FUNC_EXPORT extern
#		define APPS_COMMON_DYNAMIC_CLASS __declspec(dllimport)
#	endif
#endif

#endif // _APPS_COMMON_CONFIG_H_