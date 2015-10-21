#include <SDK/Plugins/LocalProjectPlugin.h>

#include <SDK/Project/LocalProject.h>

namespace MeegaSDK
{
	
	LocalProjectPlugin::LocalProjectPlugin()
		: ProjectPlugin()
	{

	}

	LocalProjectPlugin::~LocalProjectPlugin()
	{

	}

	uint32_t LocalProjectPlugin::id()
	{
		return PluginId::PROJECT_LOCAL;
	}

	std::unique_ptr<Project> LocalProjectPlugin::createProject(std::unique_ptr<ProjectPrivate>&& data)
	{
		return std::unique_ptr<Project>(new LocalProject(std::move(data)));
	}

	std::unique_ptr<Project> LocalProjectPlugin::openProject(std::unique_ptr<ProjectPrivate>&& data)
	{
		return std::unique_ptr<Project>(new LocalProject(std::move(data)));
	}

	QString LocalProjectPlugin::name()
	{
		return QObject::tr("Local Project");
	}

	QString LocalProjectPlugin::description()
	{
		return QObject::tr("A project stored completely on the local system.");
	}
}