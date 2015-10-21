#ifndef _MEEGA_SDK_LOCAL_PROJECT_H_
#define _MEEGA_SDK_LOCAL_PROJECT_H_

#include "Project.h"

namespace MeegaSDK
{
	class MEEGA_SDK_CLASS LocalProject : public Project
	{
	public:
		LocalProject(const LocalProject&) = delete;

		LocalProject(std::unique_ptr<ProjectPrivate>&& privParams);
		virtual ~LocalProject();
	};
}

#endif _MEEGA_SDK_LOCAL_PROJECT_H_