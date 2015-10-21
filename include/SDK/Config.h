#ifndef _MEEGA_SDK_CONFIG_H_
#define _MEEGA_SDK_CONFIG_H_

#if defined(_WIN32)
#	if defined(_DEBUG)
#		pragma comment(lib, "Qt5Guid.lib")
#		pragma comment(lib, "Qt5Cored.lib")
#		pragma comment(lib, "Qt5Widgetsd.lib")

#	else
#		pragma comment(lib, "Qt5Gui.lib")
#		pragma comment(lib, "Qt5Core.lib")
#		pragma comment(lib, "Qt5Widgets.lib")
#	endif
#endif

#ifndef _WIN32
#	define MEEGA_SDK_FUNCTION extern
#	define MEEGA_SDK_CLASS
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