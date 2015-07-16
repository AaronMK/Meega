#ifndef _RESOURCE_RESOURCE_H_
#define _RESOURCE_RESOURCE_H_

#include <Resource/Config.h>
#include <Resource/Types.h>

#include <functional>
#include <string>

/**
 * Resource contains functions and classes to support reading, writing, and serialization of data
 * to generaic ByteStreams.
 */
namespace Resource
{
	RESOURCE_DYNAMIC_FUNC_EXPORT bool rscInitialize();
	RESOURCE_DYNAMIC_FUNC_EXPORT bool rscShutdown();

	enum class MessageLevel
	{
		INFO,
		WARNING,
		CRITICAL
	};

	enum class ItemStream
	{
		NONE,
		DATA,
		METADATA
	};

	/**
	 * Stream is read only.
	 */
	static const uint32 READ_ONLY = 1;

	/**
	 * Stream is write only.
	 */
	static const uint32 WRITE_ONLY = 2;

	/**
	 * Stream supports seeking.  Usually streams that do not support seaking
	 * are sockets.
	 */
	static const uint32 CAN_SEEK = 4;

	/**
	 * Backing stream data is in memory, and can be accessed directly using pointers
	 * returned by dataPtr().
	 */
	static const uint32 MEMORY_BACKED = 8;

	/**
	 * Indicates that the stream is not valid.
	 */
	static const uint32 INVALID = 16;

	typedef std::function<void(MessageLevel, std::string &&)> MessageCallback;

	/**
	 * Sets the callback function for messages from the resource library.  The userData pointer
	 * is copied to be sent with callbacks, but no ownership is taken of that data.  This can be
	 * called before initialization.
	 */
	RESOURCE_DYNAMIC_FUNC_EXPORT bool setMessageCallback(MessageCallback &&callback);

	/**
	 * Gets the each component of the version of the library in use.
	 */
	RESOURCE_DYNAMIC_FUNC_EXPORT void libVersion(uint8 *outMajor, uint8 *outMinor, uint8 *outPatch);
}

#endif // _RESOURCE_RESOURCE_H_