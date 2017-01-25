#ifndef _ENGINE_INTERFACE_HOOKS_H_
#define _ENGINE_INTERFACE_HOOKS_H_

#include "../Config.h"

#include <string>

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
		virtual void onError(std::string&& msg);

		/**
		 * @brief
		 *  The engine will continue to operate after a warning, but may not behave as expected.
		 */
		virtual void onWarning(std::string&& msg);

		/**
		 * @brief
		 *  The engine will continue to operate after a warning, but may not behave as expected.
		 */
		virtual void onInfo(std::string&& msg);
	};

	/**
	 * @brief
	 *  Raises an error message that passed to the current InterfaceHooks.
	 */
	ENGINE_EXPORT void error(std::string&& msg);

	/**
	 * @brief
	 *  Raises a warning message that passed to the current InterfaceHooks.
	 */
	ENGINE_EXPORT void warning(std::string&& msg);

	/**
	 * @brief
	 *  Raises an info message that passed to the current InterfaceHooks.
	 */
	ENGINE_EXPORT void info(std::string&& msg);
}

#endif // _ENGINE_INTERFACE_HOOKS_H_