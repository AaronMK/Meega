#include <SDK/Project/Project.h>

#include <SDK/Internal/Project/ProjectPrivate.h>

namespace MeegaSDK
{
	Project::Project(std::unique_ptr<ProjectPrivate>&& privParams)
		: mProjectPrivate(std::move(privParams))
	{
	}

	Project::~Project()
	{

	}

	std::unique_ptr<Project> Project::openProject(QDir dir)
	{
		std::unique_ptr<ProjectPrivate> projPrivate(new ProjectPrivate());
		
		if (projPrivate->load(dir))
		{
			ProjectPlugin* plugin = projPrivate->plugin;
			return plugin->openProject(std::move(projPrivate));
		}

		return std::unique_ptr<Project>(nullptr);
	}

	bool Project::save()
	{
		Q_ASSERT(mProjectPrivate);
		return mProjectPrivate->save();
	}

	QDir Project::dataDir() const
	{
		Q_ASSERT(mProjectPrivate);
		return mProjectPrivate->directory;
	}

	QString Project::name() const
	{
		Q_ASSERT(mProjectPrivate);
		return mProjectPrivate->name;
	}
}