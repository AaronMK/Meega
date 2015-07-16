#ifndef _RESOURCE_BYTE_STREAM_H_
#define _RESOURCE_BYTE_STREAM_H_

#include <Resource/Resource.h>
#include <Resource/Types.h>

#include <type_traits>
#include <string>
#include <limits>

namespace Resource
{
	/**
	 * Base class for all data streams. 
	 */
	class RESOURCE_DYNAMIC_CLASS ByteStream
	{
	public:
		ByteStream();
		virtual ~ByteStream();

		/**
		 * Shortcut to checking validity of the stream based on set flags.
		 */
		bool isValid() const;

		/**
		 * Gets a pointer to raw data at a seek position in the sream.  This does not
		 * actually seek the stream, and will only work if the data backing the stream
		 * is in memory.
		 */
		virtual void* dataPtr(seek_t seekPos) const;

		/**
		 * Reads a block of raw data from the current seek position of the file.
		 * The seek position is moved by the number of bytes read.  If data is NULL,
		 * the seek position is simply moved forward by byteLength.
		 */
		virtual bool readRaw(void* destination, bytesize_t byteLength) = 0;

		/**
		 * Writes raw data to the file. The seek position is moved
		 * by the number of bytes written.
		 */
		virtual bool writeRaw(const void* data, bytesize_t byteLength) = 0;

		/**
		 * Seeks to the position in terms of number of bytes from the beginning
		 */
		virtual bool seek(seek_t position) = 0;

		/*
		 * Gets the current seek position on which read and write operations will take place.
		 */
		virtual seek_t getSeekPosition() const = 0;

		/**
		 * Gets the number of bytes available for reading from the current seek position.
		 */
		virtual bytesize_t bytesAvailable() const = 0;

		/**
		 * Determines if there is the specified amount of data left to read.
		 */
		virtual bool canRead(bytesize_t numBytes) = 0;

		/**
		 * Determines if the stream is capable of handling a write of the requested
		 * size at the current seek position.  If autoExpand is true, the ByteStream
		 * will attempt to expand to make it capable of handling the requested write
		 * and return true if successful.
		 */
		virtual bool canWrite(bytesize_t numBytes, bool autoExpand = false) = 0;
		
		/**
		 * For writable streams, clears all contents and resets the seek position to 0.
		 */
		virtual bool clear() = 0;

		/*
		 * Gets the flags for common properties of ByteStreams.
		 */
		uint32 getFlags() const;

	protected:
		void setFlags(uint32 mask);

	private:
		uint32 mFlags;
	};
}

#endif // _RESOURCE_BYTE_STREAM_H_