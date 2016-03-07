#ifndef _CONCURRENT_H_
#define _CONCURRENT_H_

#include "Config.h"

/**
 * @brief
 *  Contains all classes and functionality of the Concurrent library.
 */
namespace Concurrent
{
	CONCURRENT_DYNAMIC_FUNC_EXPORT bool initialize();
	CONCURRENT_DYNAMIC_FUNC_EXPORT void shutdown();

	CONCURRENT_DYNAMIC_FUNC_EXPORT unsigned int hardwareConcurrency();
}

#endif // _CONCURRENT_H_