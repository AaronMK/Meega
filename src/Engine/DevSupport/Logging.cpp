#include <Engine/DevSupport/Logging.h>

#ifdef ENGINE_DEVELOPMENT_SUPPORT

#include <StdExt/Signals/Invokable.h>
#include <StdExt/Concurrent/Mutex.h>

using namespace StdExt::Concurrent;
using namespace StdExt::Signals;
using namespace StdExt;

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

		Concurrent::MutexLocker lock(logLock);
		evtLog.invoke(lType, lSource, lSeverity, lMsg);
	}
}
#else

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

#endif