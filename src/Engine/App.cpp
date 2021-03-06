#include <Engine/App.h>

namespace Engine
{
	App::App(int argCount, char** argValues)
	{
	}

	App::~App()
	{
	}

	void App::setMainRenderTarget(GPU::RenderTarget* target)
	{
		m_RenderTarget = target;
	}

	GPU::RenderTarget* App::getMainRenderTarget()
	{
		return m_RenderTarget;
	}

	const int App::argc() const
	{
		return m_argc;
	}

	const char** App::argv() const
	{
		return m_argv;
	}

	int runApp(App &app)
	{
		Engine::Options options = app.getOptions();
		
		Engine::initialize();
		int ret = app.run();
		Engine::shutdown();

		return ret;
	}
}