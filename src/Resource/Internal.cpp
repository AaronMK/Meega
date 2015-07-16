#include "private_include/Internal.h"

#include <cassert>
#include <sstream>

namespace Resource
{
	void critical(std::string && msg)
	{
		messageCallback(MessageLevel::CRITICAL, std::forward<std::string>(msg));
	}

	void warning(std::string && msg)
	{
		messageCallback(MessageLevel::WARNING, std::forward<std::string>(msg));
	}

	void info(std::string && msg)
	{
		messageCallback(MessageLevel::INFO, std::forward<std::string>(msg));
	}

	std::vector<std::string> split(const std::string &str, const std::string &delim, bool keepEmpty)
	{
		size_t pos = 0;
		std::string token;
		std::string tempStr(str);
		std::vector<std::string> out;

		while ((pos = tempStr.find(delim)) != std::string::npos)
		{
			token = tempStr.substr(0, pos);

			if (token.size() > 0 || keepEmpty)
				out.push_back(token);

			tempStr.erase(0, pos + delim.length());
		}

		if (tempStr.size() > 0 || keepEmpty)
			out.push_back(tempStr);

		return out;
	}

	std::string join(const std::vector<std::string> &strings, const std::string &glue)
	{
		std::stringstream out;

		for (unsigned int i = 0; i < strings.size(); i++)
		{
			out << strings[i];

			if (i < strings.size() - 1)
				out << glue;
		}

		return out.str();
	}

	int strcmp(const char* left, ByteStream* stream, seek_t stringSeek)
	{
		assert(stream->getFlags() & MEMORY_BACKED != 0);

		SeekBackup seekBack(stream);
		stream->seek(stringSeek);

		uint32 stringSize = 0;
		Serializer serializer(stream);

		serializer.readUInt32(&stringSize, 1);

		const char* strData = (const char*)stream->dataPtr(stream->getSeekPosition());

		return strncmp(left, strData, stringSize);
	}
}