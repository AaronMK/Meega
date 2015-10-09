#ifndef _ENGINE_INTERFACE_HOOKS_H_
#define _ENGINE_INTERFACE_HOOKS_H_

#include "../Config.h"

#include <string>

namespace Engine
{
	/**
	 * Defines ways for the engine to communicate with a client.  The client can set up this communication
	 * by passing an InterfaceHooks object to setHooks.
	 */
	class ENGINE_DYNAMIC_CLASS InterfaceHooks
	{
	protected:
		InterfaceHooks();

	public:
		virtual ~InterfaceHooks();

		static void setHooks(InterfaceHooks* hook);

		/**
		 * An error is a condition that will prevent the engine from operating further.
		 */
		virtual void onError(std::string&& msg);

		/**
		 * The engine will continue to operate after a warning, but may not behave as expected.
		 */
		virtual void onWarning(std::string&& msg);

		/**
		 * The engine will continue to operate after a warning, but may not behave as expected.
		 */
		virtual void onInfo(std::string&& msg);
	};

	ENGINE_FUNC_EXPORT void error(std::string&& msg);
	ENGINE_FUNC_EXPORT void warning(std::string&& msg);
	ENGINE_FUNC_EXPORT void info(std::string&& msg);
}

#endif // _ENGINE_INTERFACE_HOOKS_H_