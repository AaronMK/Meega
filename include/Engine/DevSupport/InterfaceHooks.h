#ifndef _ENGINE_INTERFACE_HOOKS_H_
#define _ENGINE_INTERFACE_HOOKS_H_

#include "../Config.h"

#include <StdExt/String.h>
#include <StdExt/Signals/Event.h>

namespace Engine
{
	/**
	 * @brief
	 *  Defines ways for the engine to communicate with a client.  The client can set up this communication
	 *  by passing an InterfaceHooks object to setHooks().
	 */
	class ENGINE_EXPORT InterfaceHooks
	{
	public:
		
		template<typename T>
		using Event = StdExt::Signals::Event<T>;

		using String = StdExt::String;

		/**
		 * @brief
		 *  An error is a condition that will prevent the engine from operating further.
		 *  The returned event will be raised before the engine stops.
		 */
		static const Event<String>& errorEvent();

		/**
		 * @brief
		 *  The engine will continue to operate after a warning, but may not behave as expected.
		 *  The event returner can be used to watch for warning conditions.
		 */
		static const Event<String>& warningEvent();

		/**
		 * @brief
		 *  Returns an event taht can be used to watch for information messages.
		 */
		static const Event<String>& infoEvent();

		/**
		 * @brief
		 *  Raises an error event and stops the engine.
		 */
		static void error(const StdExt::String& msg);

		/**
		 * @brief
		 *  Raises a warning message.
		 */
		static void warning(const StdExt::String& msg);

		/**
		 * @brief
		 *  Raises an info message that passed to the current InterfaceHooks.
		 */
		static void info(const StdExt::String& msg);
	};
}

#endif // _ENGINE_INTERFACE_HOOKS_H_