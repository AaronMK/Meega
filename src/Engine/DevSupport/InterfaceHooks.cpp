#include <Engine/DevSupport/InterfaceHooks.h>

using namespace StdExt::Signals;
using namespace StdExt;

#ifdef ENGINE_DEVELOPMENT_SUPPORT

#include <Concurrent/Mutex.h>
#include <Concurrent/MutexLocker.h>

namespace Engine
{
	Concurrent::Mutex iHooksLock;

	Invokable<String> evtError;
	Invokable<String> evtWarning;
	Invokable<String> evtInfo;

	const Event<String>& InterfaceHooks::errorEvent()
	{
		return evtError;
	}

	const Event<String>& InterfaceHooks::warningEvent()
	{
		return evtWarning;
	}

	const Event<String>& InterfaceHooks::infoEvent()
	{
		return evtInfo;
	}

	void InterfaceHooks::error(const StdExt::String& msg)
	{
		Concurrent::MutexLocker lock(&iHooksLock);
		evtError.invoke(msg);
	}
	
	void InterfaceHooks::warning(const StdExt::String& msg)
	{
		Concurrent::MutexLocker lock(&iHooksLock);
		evtWarning.invoke(msg);
	}

	void InterfaceHooks::info(const StdExt::String& msg)
	{
		Concurrent::MutexLocker lock(&iHooksLock);
		evtInfo.invoke(msg);
	}
}
#else
namespace Engine
{
	Event<String> evtNull;

	const Event<String>& InterfaceHooks::errorEvent()
	{
		return evtNull;
	}

	const Event<String>& InterfaceHooks::warningEvent()
	{
		return evtNull;
	}

	const Event<String>& InterfaceHooks::infoEvent()
	{
		return evtNull;
	}

	void InterfaceHooks::error(const StdExt::String& msg)
	{
	}

	void InterfaceHooks::warning(const StdExt::String& msg)
	{
	}

	void InterfaceHooks::info(const StdExt::String& msg)
	{
	}
}
#endif