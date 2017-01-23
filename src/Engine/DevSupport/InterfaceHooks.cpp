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

	void InterfaceHooks::onError(std::string&& msg)
	{
	}
	
	void InterfaceHooks::onWarning(std::string&& msg)
	{
	}
	
	void InterfaceHooks::onInfo(std::string&& msg)
	{
	}

	///////////////////////////////////////////

#ifdef ENGINE_DEVELOPMENT_SUPPORT

	void error(std::string&& msg)
	{
		Concurrent::MutexLocker lock(&iHooksLock);

		if ( NULL != currentHooks)
			currentHooks->onError(std::forward<std::string>(msg));
	}
	
	void warning(std::string&& msg)
	{
		Concurrent::MutexLocker lock(&iHooksLock);

		if ( NULL != currentHooks)
			currentHooks->onWarning(std::forward<std::string>(msg));
	}

	void info(std::string&& msg)
	{
		Concurrent::MutexLocker lock(&iHooksLock);

		if ( NULL != currentHooks)
			currentHooks->onInfo(std::forward<std::string>(msg));
	}

#else
	void error(std::string&& msg){}
	void warning(std::string&& msg){}
	void info(std::string&& msg){}
#endif
}