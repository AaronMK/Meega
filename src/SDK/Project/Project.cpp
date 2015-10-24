#include <SDK/Project/Project.h>

#include <SDK/Internal/Project/ProjectPrivate.h>

namespace MeegaSDK
{

	//////////////////////////////////////////////////////////////////

	Project::Project(std::unique_ptr<ProjectPrivate>&& privParams)
		: mProjectPrivate(std::move(privParams))
	{

	}

	Project::~Project()
	{

	}

	std::unique_ptr<Project> Project::openProject(QDir dir)
	{
		return std::unique_ptr<Project>(nullptr);
	}

	QDir Project::dataDir() const
	{
		return mProjectPrivate->projectDir;
	}

	QString Project::name() const
	{
		return mProjectPrivate->projectName;
	}
}