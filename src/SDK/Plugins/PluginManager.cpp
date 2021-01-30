#include <SDK/Plugins/PluginManager.h>

#include <QtCore/QMap>
#include <QtCore/QLibrary>
#include <QtCore/QMultiMap>
#include <QtCore/QWeakPointer>
#include <QtCore/QSharedPointer>

#include <SDK/Plugins/LocalProjectPlugin.h>

namespace MeegaSDK
{
	namespace PluginManager
	{
		static QMultiMap<Plugin::Type, QWeakPointer<Plugin>> pluginTypeIndex;
		static QMap<uint32_t, QSharedPointer<Plugin>> pluginIdIndex;

		void loadStandardPlugins()
		{
			loadPlugin(std::unique_ptr<Plugin>(new LocalProjectPlugin()));
		}

		bool loadPlugin(QString modulePath)
		{
			if (QLibrary::isLibrary(modulePath))
			{
				QLibrary lib(modulePath);
				PluginExportFunc func = (PluginExportFunc)lib.resolve("meegaCreatePlugins");

				if (nullptr != func)
				{
					std::vector<std::unique_ptr<Plugin>> plugins(func());

					for (size_t i = 0; i < plugins.size(); i++)
						loadPlugin(std::move(plugins[i]));

					return true;
				}
			}

			return false;
		}

		bool loadPlugin(std::unique_ptr<Plugin>&& plugin)
		{
			if (plugin.get() == nullptr || pluginIdIndex.contains(plugin->id()) )
				return false;

			QSharedPointer<Plugin> ptrPlugin(plugin.release());

			pluginIdIndex.insert(ptrPlugin->id(), ptrPlugin);
			pluginTypeIndex.insert(ptrPlugin->type(), ptrPlugin);

			return true;
		}

		void clearPlugins()
		{
			pluginTypeIndex.clear();
			pluginIdIndex.clear();
		}

		QVector<ProjectPlugin*> getProjectPlugins()
		{
			QList<QWeakPointer<Plugin>> qList(pluginTypeIndex.values(Plugin::Type::Project));

			QVector<ProjectPlugin*> ret;
			ret.reserve(qList.size());

			Q_FOREACH(QWeakPointer<Plugin> ptrPlugin, qList)
			{
				ret.append(dynamic_cast<ProjectPlugin*>(ptrPlugin.toStrongRef().data()));
			}

			return ret;
		}

		Plugin* getPluginById(uint32_t id)
		{
			QMap<uint32_t, QSharedPointer<Plugin>>::iterator itr = pluginIdIndex.find(id);

			return (itr != pluginIdIndex.end()) ? itr.value().data() : nullptr;
		}
	}
}