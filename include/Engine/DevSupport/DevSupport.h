#ifndef _ENGINE_DEV_SUPPORT_H_
#define _ENGINE_DEV_SUPPORT_H_

#include "../Config.h"

#ifdef ENGINE_DEVELOPMENT_SUPPORT

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

#include <QtCore/QThread>

namespace Engine
{
	/**
	 * @brief
	 *  In development builds the engine performs operations that must be done
	 *  in the context of the user interface thread.  This function sets that thread.
	 */
	ENGINE_EXPORT void setGuiThread(QThread* thread);
}

#endif // ENGINE_DEVELOPMENT_SUPPORT

#endif // _ENGINE_DEV_SUPPORT_H_