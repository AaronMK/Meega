#include "include/EditorApp.qt.h"

#if defined(_WIN32)
#	if defined(_DEBUG)
#		pragma comment(lib, "Qt6EntryPointd.lib")
#		pragma comment(lib, "Qt6Cored.lib")
#		pragma comment(lib, "Qt6Widgetsd.lib")
#	else
#		pragma comment(lib, "Qt6EntryPoint.lib")
#		pragma comment(lib, "Qt6Core.lib")
#		pragma comment(lib, "Qt6Widgets.lib")
#	endif

#	pragma comment(lib, "SDK.lib")
#	pragma comment(lib, "Engine.lib")
#endif

int main(int argc, char** argv)
{
	EditorApp app(argc, argv);
	return app.exec();
}