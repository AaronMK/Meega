#ifndef _RESOURCE_CONFIG_H_
#define _RESOURCE_CONFIG_H_

/** \def RESOURCE_DYNAMIC
* Defined when the Engine is being built to support dynamic linking.
*/

//////////////////////////////////////
///// DO NOT EDIT BELOW THIS LINE ////
//////////////////////////////////////

#if defined(_WIN32)
#	ifndef NOMINMAX
#		define NOMINMAX
#		undef min
#		undef max
#	endif
#endif

#if !defined(RESOURCE_DYNAMIC)
#	define RESOURCE_DYNAMIC_FUNC_EXPORT
#	define RESOURCE_DYNAMIC_CLASS
#	define RESOURCE_DYNAMIC_FUNC_DECLARE
#elif defined(_WIN32)
#	if defined(RESOURCE_COMPILE)
#		define RESOURCE_DYNAMIC_FUNC_EXPORT __declspec(dllexport)
#		define RESOURCE_DYNAMIC_CLASS __declspec(dllexport)
#	else
#		define RESOURCE_DYNAMIC_FUNC_EXPORT __declspec(dllimport)
#		define RESOURCE_DYNAMIC_CLASS __declspec(dllimport)
#	endif
#endif

#endif // _RESOURCE_CONFIG_H_