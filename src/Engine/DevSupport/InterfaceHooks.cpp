#include <Engine/DevSupport/InterfaceHooks.h>

#include <iostream>

#include <Concurrent/Mutex.h>
#include <Concurrent/MutexLocker.h>

namespace Engine
{
	static InterfaceHooks* currentHooks = NULL;
	static Concurrent::Mutex iHooksLock;

	InterfaceHooks::InterfaceHooks()
	{
	}

	InterfaceHooks::~InterfaceHooks()
	{
	}
	
	void InterfaceHooks::setHooks(InterfaceHooks* hook)
	{
		Concurrent::MutexLocker lock(&iHooksLock);
		currentHooks = hook;
	}

	void InterfaceHooks::onError(const StdExt::String& msg)
	{
	}
	
	void InterfaceHooks::onWarning(const StdExt::String& msg)
	{
	}
	
	void InterfaceHooks::onInfo(const StdExt::String& msg)
	{
	}

	///////////////////////////////////////////

#ifdef ENGINE_DEVELOPMENT_SUPPORT

	void error(const StdExt::String& msg)
	{
		Concurrent::MutexLocker lock(&iHooksLock);

		if ( NULL != currentHooks)
			currentHooks->onError(msg);
	}
	
	void warning(const StdExt::String& msg)
	{
		Concurrent::MutexLocker lock(&iHooksLock);

		if ( NULL != currentHooks)
			currentHooks->onWarning(msg);
	}

	void info(const StdExt::String& msg)
	{
		Concurrent::MutexLocker lock(&iHooksLock);

		if ( NULL != currentHooks)
			currentHooks->onInfo(msg);
	}

#else
	void error(std::string&& msg){}
	void warning(std::string&& msg){}
	void info(std::string&& msg){}
#endif
}