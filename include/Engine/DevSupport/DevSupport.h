#ifndef _ENGINE_DEV_SUPPORT_H_
#define _ENGINE_DEV_SUPPORT_H_

#include <Engine/Config.h>

#ifdef ENGINE_DEVEOPMENT_SUPPORT

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

#endif // ENGINE_DEVEOPMENT_SUPPORT

#endif // _ENGINE_DEV_SUPPORT_H_