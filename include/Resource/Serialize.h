#ifndef _RESOURCE_SERIALIZE_H_
#define _RESOURCE_SERIALIZE_H_

#include<Resource/Config.h>

#include <cassert>
#include <cstdint>
#include <string>

namespace Resource
{
	class ByteStream;

	namespace Serialize
	{
		template<typename T>
		bool read(ByteStream* stream, T *out)
		{
			// Read needs to be specialized for the type.
			assert(false);
		}

		template<typename T>
		bool write(ByteStream* stream, const T &val)
		{
			// Read needs to be specialized for the type.
			assert(false);
		}

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool read<uint16_t>(ByteStream* stream, uint16_t *out);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool write<uint16_t>(ByteStream* stream, const uint16_t &val);


		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool read<std::string>(ByteStream* stream, std::string *out);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool write<std::string>(ByteStream* stream, const std::string &val);
	}
}

#endif // _RESOURCE_SERIALIZE_H_