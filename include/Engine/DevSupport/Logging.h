#ifndef _ENGINE_DEV_SUPPORT_H_
#define _ENGINE_DEV_SUPPORT_H_

#include "../Config.h"

#include <functional>
#include <string>

namespace Engine
{
	enum class LogSource
	{
		GPU,
		Engine,
		GraphicsApi,
		WindowSystem,
		ShaderCompiler,
		ThirdParty,
		Application,
		Other
	};

	enum class LogType
	{
		Info,
		Deprecated,
		UndefinedBehavior,
		Protability,
		Performance,
		Marker,
		PushGroup,
		PopGroup,
		Warning,
		Error,
		Other
	};

	enum class LogSeverity
	{
		Info,
		Low,
		Medium,
		High
	};

	typedef std::function<void(LogType, LogSource, LogSeverity, std::string&&)> LogCallback;
}

#endif // _ENGINE_DEV_SUPPORT_H_