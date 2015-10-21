#ifndef _MEEGA_SDK_LOCAL_PROJECT_PLUGIN_H_
#define _MEEGA_SDK_LOCAL_PROJECT_PLUGIN_H_

#include "ProjectPlugin.h"

namespace MeegaSDK
{
	class MEEGA_SDK_CLASS LocalProjectPlugin : public ProjectPlugin
	{
	public:
		LocalProjectPlugin();
		virtual ~LocalProjectPlugin();

		virtual uint32_t id() override;

		virtual std::unique_ptr<Project> createProject(std::unique_ptr<ProjectPrivate>&& data) override;
		virtual std::unique_ptr<Project> openProject(std::unique_ptr<ProjectPrivate>&& data) override;

		virtual QString name() override;
		virtual QString description() override;
	};
}

#endif _MEEGA_SDK_LOCAL_PROJECT_H_