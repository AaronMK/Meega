#include "include/EditorApp.qt.h"

#if defined(_WIN32)
#	if defined(_DEBUG)
#		pragma comment(lib, "qtmaind.lib")
#		pragma comment(lib, "Qt5Cored.lib")
#		pragma comment(lib, "Qt5Widgetsd.lib")
#	else
#		pragma comment(lib, "qtmain.lib")
#		pragma comment(lib, "Qt5Core.lib")
#		pragma comment(lib, "Qt5Widgets.lib")
#	endif

#		pragma comment(lib, "SDK.lib")
#endif

int main(int argc, char** argv)
{
	EditorApp app(argc, argv);
	return app.exec();
}