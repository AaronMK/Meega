#ifndef _CONCURRENT_H_
#define _CONCURRENT_H_

#include <Concurrent/Config.h>

/**
 * Contains all classes and functionality of the Concurrent library.
 */
namespace Concurrent
{
	CONCURRENT_DYNAMIC_FUNC_EXPORT bool initialize();
	CONCURRENT_DYNAMIC_FUNC_EXPORT void shutdown();
}

#endif // _CONCURRENT_H_