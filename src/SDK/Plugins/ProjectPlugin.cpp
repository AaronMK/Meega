#include <SDK/Plugins/ProjectPlugin.h>

namespace MeegaSDK
{
	ProjectPlugin::ProjectPlugin()
		: Plugin()
	{
	}

	ProjectPlugin::~ProjectPlugin()
	{

	}

	Plugin::Type ProjectPlugin::type()
	{
		return Type::Project;
	}
}