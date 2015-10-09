#ifndef _RESOURCE_SERIALIZE_H_
#define _RESOURCE_SERIALIZE_H_

#include "Config.h"
#include "Types.h"

#include <cassert>
#include <string>

namespace Resource
{
	class ByteStream;

	/**
	 * @todo
	 *  Make these endian aware.  Get policy for checking reads for the proper type. 
	 */
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
			// Write needs to be specialized for the type.
			assert(false);
		}

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool read<uint8_t>(ByteStream* stream, uint8_t *out);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool write<uint8_t>(ByteStream* stream, const uint8_t &val);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool read<uint16_t>(ByteStream* stream, uint16_t *out);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool write<uint16_t>(ByteStream* stream, const uint16_t &val);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool read<uint32_t>(ByteStream* stream, uint32_t *out);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool write<uint32_t>(ByteStream* stream, const uint32_t &val);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool read<int8_t>(ByteStream* stream, int8_t *out);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool write<int8_t>(ByteStream* stream, const int8_t &val);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool read<int16_t>(ByteStream* stream, int16_t *out);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool write<int16_t>(ByteStream* stream, const int16_t &val);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool read<int32_t>(ByteStream* stream, int32_t *out);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool write<int32_t>(ByteStream* stream, const int32_t &val);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool read<float32_t>(ByteStream* stream, float32_t *out);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool write<float32_t>(ByteStream* stream, const float32_t &val);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool read<float64_t>(ByteStream* stream, float64_t *out);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool write<float64_t>(ByteStream* stream, const float64_t &val);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool read<std::string>(ByteStream* stream, std::string *out);

		template<>
		RESOURCE_DYNAMIC_FUNC_EXPORT bool write<std::string>(ByteStream* stream, const std::string &val);
	}
}

#endif // _RESOURCE_SERIALIZE_H_