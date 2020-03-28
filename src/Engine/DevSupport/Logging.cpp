#include <Engine/DevSupport/Logging.h>

using namespace StdExt::Signals;
using namespace StdExt;

#ifdef ENGINE_DEVELOPMENT_SUPPORT

#include <Concurrent/Mutex.h>
#include <Concurrent/MutexLocker.h>

namespace Engine
{
	Invokable<Logging::Type, Logging::Source, Logging::Severity, StdExt::String> evtLog;
	Concurrent::Mutex logLock;

	const Logging::event_t& Logging::getEvent()
	{
		return evtLog;
	}

	void Logging::log(Logging::Type lType, Logging::Source lSource, Logging::Severity lSeverity, const StdExt::String& lMsg)
	{

		Concurrent::MutexLocker lock(&logLock);
		evtLog.invoke(lType, lSource, lSeverity, lMsg);
	}
}
#else
{
	namespace Engine
	{
		Invokable<Logging::Type, Logging::Source, Logging::Severity, StdExt::String> evtLog;

		const Logging::event_t& Logging::getEvent()
		{
			return evtLog;
		}

		void Logging::log(Type lType, Source lSource, Severity lSeverity, const StdExt::String& lMsg)
		{
		}
	}
}
#endif