#include <Engine/DevSupport/InterfaceHooks.h>


#ifdef ENGINE_DEVELOPMENT_SUPPORT

#include <StdExt/Concurrent/Mutex.h>
#include <StdExt/Signals/Invokable.h>

using namespace StdExt::Concurrent;
using namespace StdExt::Signals;
using namespace StdExt;

namespace Engine
{
	Mutex iHooksLock;

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
		MutexLocker lock(iHooksLock);
		evtError.invoke(msg);
	}
	
	void InterfaceHooks::warning(const StdExt::String& msg)
	{
		MutexLocker lock(iHooksLock);
		evtWarning.invoke(msg);
	}

	void InterfaceHooks::info(const StdExt::String& msg)
	{
		MutexLocker lock(iHooksLock);
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