#ifndef _ENGINE_DEV_SUPPORT_H_
#define _ENGINE_DEV_SUPPORT_H_

#include "../Config.h"

#include <StdExt/String.h>
#include <StdExt/Signals/Event.h>

#include <functional>

namespace Engine
{
	class Logging
	{
	public:
		enum class Source
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

		enum class Type
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

		enum class Severity
		{
			Info,
			Low,
			Medium,
			High
		};

		using event_t = StdExt::Signals::Event<Type, Source, Severity, StdExt::String>;

		static const event_t& getEvent();

		static void log(Type lType, Source lSource, Severity lSeverity, const StdExt::String& lMsg);
	};


}

#endif // _ENGINE_DEV_SUPPORT_H_