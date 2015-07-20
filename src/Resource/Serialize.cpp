#include <Resource/Serialize.h>

#include <Resource/ByteStream.h>

namespace Resource
{
	namespace Serialize
	{
		template<>
		bool read<uint16_t>(ByteStream* stream, uint16_t *out)
		{
			return stream->readRaw(out, sizeof(uint16_t));
		}

		template<>
		bool write<uint16_t>(ByteStream* stream, const uint16_t &val)
		{
			return stream->writeRaw(&val, sizeof(uint16_t));
		}

		template<>
		bool read<std::string>(ByteStream* stream, std::string *out)
		{
			seek_t back = stream->getSeekPosition();

			uint16_t length;
			if (read<uint16_t>(stream, &length))
			{
				std::string str;
				str.resize(length);
				
				if (stream->readRaw((void*)str.data(), length))
				{
					*out = std::move(str);
					return true;
				}
			}

			stream->seek(back);
			return false;
		}

		template<>
		bool write<std::string>(ByteStream* stream, const std::string &val)
		{
			seek_t back = stream->getSeekPosition();
			uint16_t length = static_cast<uint16_t>(val.length());

			if (write(stream, length) && stream->writeRaw(val.data(), length))
				return true;

			stream->seek(back);
			return false;
		}
	}
}