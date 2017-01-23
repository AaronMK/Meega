#ifndef _ENGINE_APP_H_
#define _ENGINE_APP_H_

#include "Engine.h"
#include "Options.h"

#include <GPU/RenderTarget.h>

namespace Engine
{
	/**
	 * Bass class for applications that use the engine.  In development builds, a dynamic library
	 * that exports an app object can be passed to Engine tools for aid in development.
	 * For distribution, app objects will run after initialization of the engine is complete.
	 *
	 * Either way, the class which defines that app is declared using the ENGINE_DECLARE_APP_CLASS
	 * macro somewhere in the implementation, and the Engine takes it from there.
	 *
	 * The macros expect the constructor to take the standard (int argc, char** argv) arguments, and
	 * will make the command line parameters, with Runner parameters parsed away, available to the app
	 * via member functions.
	 *
	 * This class also defines how the engine or engine tools will interface with the application once
	 * launched.
	 */
	class ENGINE_DYNAMIC_CLASS App
	{
	public:
		App(int argCount, char** argValues);
		virtual ~App();

		/**
		 * Obtains the options that will be used to initialize the engine for running the app.
		 */
		virtual Engine::Options getOptions() = 0;

		/**
		 * The main function for the app.  This should not return until the app has finished running.
		 */
		virtual int run() = 0;

		/**
		 * Called when the resolution for the App's render target changes.
		 */
		virtual void resolutionChanged(int x, int y) = 0;

		/**
		 * The engine will call this if an exit is requested.  The app should handle its shutdown code
		 * and cause run() to promptly complete.
		 */
		virtual void exitRequested() = 0;

		void setMainRenderTarget(GPU::RenderTarget* target);
		GPU::RenderTarget* getMainRenderTarget();

	protected:
		const int argc() const;
		const char** argv() const;

	private:
		GPU::RenderTarget* m_RenderTarget;

		int m_argc;
		char** m_argv;
	};

	typedef App* (appCreateFunc)(int argc, char** argv);

	ENGINE_FUNC_EXPORT int runApp(App &app);
}

#if defined ENGINE_BUILD
#	define ENGINE_DECLARE_APP_CLASS(cls)
#else
#	if defined(ENGINE_DEVELOPMENT_SUPPORT)
#		define ENGINE_DECLARE_APP_CLASS(cls) extern "C" __declspec(dllexport) Engine::App* createAppObject(int argc, char** argv) { return new cls(argc, argv); };
#	else
#		define ENGINE_DECLARE_APP_CLASS(cls) int main(int argc, char** argv) { return Engine::runApp(cls(argc, argv)); };
#	endif
#endif

#endif // _ENGINE_APP_H_