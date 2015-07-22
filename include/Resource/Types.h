#ifndef _RESOURCE_TYPES_H_
#define _RESOURCE_TYPES_H_

#include <Resource/Config.h>

#include <cstdint>

namespace Resource
{
	typedef float float32_t;
	typedef double float64_t;

	// Types to support bytestream metrics
	typedef uint32_t seek_t;
	typedef size_t bytesize_t;
}

#endif // _RESOURCE_TYPES_H_