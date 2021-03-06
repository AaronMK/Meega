#if defined(_WIN32)
#	if defined(_DEBUG)
#		pragma comment(lib, "Qt6EntryPointd.lib")
#	else
#		pragma comment(lib, "Qt6EntryPoint.lib")
#	endif

#	pragma comment(lib, "GPU.lib")
#	pragma comment(lib, "SDK.lib")
#	pragma comment(lib, "Engine.lib")
#	pragma comment(lib, "AppsCommon.lib")
#endif

#include "TriangleApp.qt.h"

#include <Engine/Engine.h>

using namespace Concurrent;

int main(int argc, char** argv)
{
	Engine::initialize();
	int ret;

	// Scope the application so Engine shutdown occurs
	// after application destruction.
	{
		TriangleApp app(argc, argv);
		ret = app.exec();
	}

	Engine::shutdown();

	return ret;
}