#ifndef _RESOURCE_TYPES_H_
#define _RESOURCE_TYPES_H_

#include <Resource/Config.h>

#include <stdint.h>

namespace Resource
{
	typedef int8_t int8;
	typedef uint8_t uint8;

	typedef int16_t int16;
	typedef uint16_t uint16;

	typedef int32_t int32;
	typedef uint32_t uint32;

	typedef int64_t int64;
	typedef uint64_t uint64;

	typedef float float32;
	typedef double float64;

	// Types to support bytestream metrics
	typedef uint32 seek_t;
	typedef size_t bytesize_t;

}

#endif // _RESOURCE_TYPES_H_