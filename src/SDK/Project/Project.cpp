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

	QDir Project::dataDir() const
	{
		return mProjectPrivate->projectDir;
	}
}