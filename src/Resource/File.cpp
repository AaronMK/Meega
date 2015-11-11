#include <Resource/File.h>

#include "private_include/Internal.h"

#include <climits>

namespace Resource
{
	File::File()
		: mFile(nullptr)
	{

	}

	File::File(const char* path, bool readonly)
		: mFile(nullptr)
	{
		open(path, readonly);
	}

	File::File(File &&other)
	{
		mFile = other.mFile;
		other.mFile = nullptr;
	}

	File::~File()
	{
		close();
	}

	bool File::readRaw(void* destination, bytesize_t byteLength)
	{
		if (nullptr == mFile)
			return false;

		seek_t backSeek = getSeekPosition();

		size_t byteCount = byteLength;
		size_t elementsRead;

		if (destination)
			elementsRead = fread(destination, byteCount, 1, mFile);
		else
			elementsRead = seek(getSeekPosition() + byteLength) ? 1 : 0;

		if (elementsRead >= 1)
		{
			return true;
		}
		else
		{
			warning("Reading of raw data from a file failed.");
			seek(backSeek);
			return false;
		}
	}

	bool File::writeRaw(const void* data, bytesize_t byteLength)
	{
		if (NULL == mFile)
			return false;

		seek_t backSeek = getSeekPosition();

		size_t byteCount = byteLength;
		size_t elementsWritten = fwrite(data, byteCount, 1, mFile);

		if (elementsWritten >= 1)
		{
			return true;
		}
		else
		{
			warning("Writing of raw data to a file failed.");
			seek(backSeek);
			return false;
		}
	}

	bool File::seek(seek_t position)
	{
		if (NULL == mFile)
			return false;

		// Check for overflow
		if (position > (int64_t)std::numeric_limits<long>::max())
		{
			warning("Attempt was made to seek past the supported max file size.");
			return false;
		}

		return ( 0 == fseek(mFile, (long)position, SEEK_SET) );
	}

	seek_t File::getSeekPosition() const
	{
		if (NULL != mFile)
			return ftell(mFile);

		return 0;
	}

	bytesize_t File::bytesAvailable() const
	{
		File* nonConstFile = const_cast<File*>(this);

		seek_t currentSeek = nonConstFile->getSeekPosition();
		seek_t maxSeek = 0;

		bytesize_t ret;

		fseek(mFile, 0, SEEK_END);
		maxSeek = nonConstFile->getSeekPosition();

		ret = maxSeek - currentSeek;

		nonConstFile->seek(currentSeek);
		return ret;
	}

	bool File::canRead(bytesize_t numBytes)
	{
		if (NULL == mFile)
			return false;

		long int currentSeek = ftell(mFile);

		if (currentSeek >= static_cast<long int>(std::numeric_limits<seek_t>::max()))
			return false;

		seek_t maxSeek = 0;

		if (0 == fseek(mFile, 0, SEEK_END))
		{
			maxSeek = ftell(mFile);
			bool ret = (numBytes <= maxSeek - currentSeek);

			seek(currentSeek);
			return ret;
		}

		return false;
	}

	bool File::canWrite(bytesize_t numBytes, bool autoExpand)
	{
		return ( 0 == ( getFlags() | READ_ONLY) );
	}


	bool File::clear()
	{
		if ( NULL != mFile && (0 == (getFlags() | READ_ONLY)) )
		{
			mFile = freopen(NULL, "w+", mFile);
			return (NULL != mFile);
		}

		return false;
	}

	bool File::open(const char* path, bool readonly)
	{
		if (nullptr != mFile)
			return false;

		if (readonly)
		{
			setFlags(READ_ONLY | CAN_SEEK);
			mFile = fopen(path, "rb");
		}
		else
		{
			setFlags(CAN_SEEK);

			if ( exists(path) )
				mFile = fopen(path, "rb+");
			else
				mFile = fopen(path, "ab+");
		}

		if (mFile == nullptr)
			perror("fopen");

		return (nullptr != mFile);
	}

	void File::close()
	{
		
		fclose(mFile);
		mFile = nullptr;
	}

	bool File::isOpen()
	{
		return (nullptr != mFile);
	}

	FILE* File::rawHandle()
	{
		return mFile;
	}

	File& File::operator=(File &&other)
	{
		if (mFile != other.mFile)
		{
			if (mFile)
				fclose(mFile);

			mFile = other.mFile;
			other.mFile = nullptr;
		}

		return *this;
	}

	bool File::exists(const char* path)
	{
		FILE* testFile = fopen(path, "rb");

		if (NULL != testFile)
		{
			fclose(testFile);
			return true;
		}

		return false;
	}
}