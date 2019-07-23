#ifndef _ENGINE_INTERFACE_HOOKS_H_
#define _ENGINE_INTERFACE_HOOKS_H_

#include "../Config.h"

#include <StdExt/String.h>

namespace Engine
{
	/**
	 * @brief
	 *  Defines ways for the engine to communicate with a client.  The client can set up this communication
	 *  by passing an InterfaceHooks object to setHooks().
	 */
	class ENGINE_EXPORT InterfaceHooks
	{
	protected:
		InterfaceHooks();

	public:
		virtual ~InterfaceHooks();

		static void setHooks(InterfaceHooks* hook);

		/**
		 * @brief
		 *  An error is a condition that will prevent the engine from operating further.
		 */
		virtual void onError(const StdExt::String& msg);

		/**
		 * @brief
		 *  The engine will continue to operate after a warning, but may not behave as expected.
		 */
		virtual void onWarning(const StdExt::String& msg);

		/**
		 * @brief
		 *  The engine will continue to operate after a warning, but may not behave as expected.
		 */
		virtual void onInfo(const StdExt::String& msg);
	};

	/**
	 * @brief
	 *  Raises an error message that passed to the current InterfaceHooks.
	 */
	ENGINE_EXPORT void error(const StdExt::String& msg);

	/**
	 * @brief
	 *  Raises a warning message that passed to the current InterfaceHooks.
	 */
	ENGINE_EXPORT void warning(const StdExt::String& msg);

	/**
	 * @brief
	 *  Raises an info message that passed to the current InterfaceHooks.
	 */
	ENGINE_EXPORT void info(const StdExt::String& msg);
}

#endif // _ENGINE_INTERFACE_HOOKS_H_