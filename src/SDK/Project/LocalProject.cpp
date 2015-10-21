#include <SDK/Project/LocalProject.h>


namespace MeegaSDK
{
	LocalProject::LocalProject(std::unique_ptr<ProjectPrivate>&& privParams)
		: Project(std::move(privParams))
	{

	}

	LocalProject::~LocalProject()
	{

	}
}