#ifndef _MEEGA_SDK_PLUGIN_H_
#define _MEEGA_SDK_PLUGIN_H_

#include "../Config.h"

#include <stdint.h>

#include <memory>
#include <vector>

#ifndef _WIN32
#	define MEEGA_SDK_EXPORT_FUNC
#else
#	define MEEGA_SDK_EXPORT_FUNC __declspec(dllexport)
#endif

namespace MeegaSDK
{
	/**
	 * @brief
	 *  The base class for all plugins.
	 *
	 * @details
	 *  Each plugin for the Meega tools will return a single object of the Plugin type.  This object is
	 *  used as the interface for interacting with and adding custom functionality to the system.
	 *
	 *  Dynamic libraries containing plugins will export a function of type PluginExportFunc with the name
	 *  meegaCreatePlugins.  MEEGA_SDK_EXPORT_FUNC is a utility macro for this purpose.
	 */
	class MEEGA_SDK_CLASS Plugin
	{
	public:
		Plugin(const Plugin&) = delete;

		Plugin();
		virtual ~Plugin();

		/**
		 * @brief
		 *  The plugin types known to the system.
		 */
		enum class Type
		{
			Project,
			Importer
		};

		/**
		 * @brief
		 *  All plugins have a unique identifier that is, among other things, used to link objects stored in a project
		 *  back to the plugin that created them and works with them.  This function must be implemented to return that
		 *  id.
		 */
		virtual uint32_t id() = 0;

		/**
		 * @brief
		 *  Returns the system recognized plugin type.
		 */
		virtual Type type() = 0;

		/**
		 * @brief
		 *  Base plugin id for plugins that are are distrubted and considered a standard part of
		 *  Meega.
		 */
		static const uint32_t ID_MEEGA_BASE = 0;

		/**
		 * @brief
		 *  Base id for plugins that distributed and maintained separately from the base Meega package.
		 *  They must be unique among plugins, and blocks will typically be assigned to a plugin vender.
		 */
		static const uint32_t ID_THIRD_PARTY_BASE = 0x40000000;

		/**
		 * @brief
		 *  All ids above this value are free to be used as an orginization or project sees fit.
		 */
		static const uint32_t ID_ORG_BASE = 0x80000000;
	};

	/**
	 * @brief
	 *  Function signature for creating and returning Plugin objects to the Meega tools.
	 */
	typedef std::vector<std::unique_ptr<Plugin>> (*PluginExportFunc)();

	/**
	 * @brief
	 *  This serves as a single namespace for plugin id definitions.
	 */
	namespace PluginId
	{
		static const uint32_t INVALID = Plugin::ID_MEEGA_BASE;
		static const uint32_t PROJECT_LOCAL = Plugin::ID_MEEGA_BASE + 1;
		static const uint32_t PROJECT_GIT   = Plugin::ID_MEEGA_BASE + 2;
	}
}

#endif // _MEEGA_SDK_PLUGIN_H_