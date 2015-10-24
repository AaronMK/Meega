#ifndef _MEEGA_SDK_PLUGIN_MANAGER_H_
#define _MEEGA_SDK_PLUGIN_MANAGER_H_

#include "ProjectPlugin.h"

#include <QtCore/QString>
#include <QtCore/QVector>

#include <memory>

namespace MeegaSDK
{
	namespace PluginManager
	{
		MEEGA_SDK_FUNCTION void loadStandardPlugins();

		MEEGA_SDK_FUNCTION bool loadPlugin(QString modulePath);
		MEEGA_SDK_FUNCTION bool loadPlugin(std::unique_ptr<Plugin>&& plugin);

		MEEGA_SDK_FUNCTION void clearPlugins();

		MEEGA_SDK_FUNCTION QVector<ProjectPlugin*> getProjectPlugins();

		MEEGA_SDK_FUNCTION Plugin* getPluginById(uint32_t id);
	}
}

#endif // _MEEGA_SDK_PLUGIN_MANAGER_H_