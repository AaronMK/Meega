#ifndef _RESOURCE_INTERNAL_H_
#define _RESOURCE_INTERNAL_H_

#include <Resource/Resource.h>
#include <Resource/ByteStream.h>

#include <functional>
#include <limits>
#include <string>
#include <vector>

namespace Resource
{
	///////// Archive Structure //////////////
	// uint8               - version major
	// uint8               - version minor
	// uint8               - version patch
	// uint8               - endianess (0 = little, 1 = big)
	// seek_t              - seek position of first folder
	// Header Structure    - size of file header data
	// seek_t              - item data begin
	// Folder Structure(s) - folder structures in the archive,
	//                       first is root and rest are sub-folders of root.
	// raw data            - item data
	/////////////////////////////////////////


	///////// Header Structure //////////////
	// bytesize_t       - header data size
	// raw data         - header data
	/////////////////////////////////////////

	///////// Item Structure //////////////
	// seek_t           - data location
	// bytesize_t       - data size
	// bytesize_t       - metadata size
	// raw data         - metadata
	/////////////////////////////////////////

	///////// Folder Structure ///////////
	// bytesize_t       - listing size (includes all data from listing size to END_FOLDER inclusive)
	// seek_t           - item data begin (will include data of all subfolder items as well)
	// bytesize_t       - item data size
	// 
	// (if subfolders)
	//		uint16           - BEGIN_SUBFOLDER
	//		string           - sub-folder name
	//		seek_t           - folder structure location
	//       .......................
	//
	// (if items)
	//		uint16           - BEGIN_ITEM
	//		string           - item name
	//		Item Structure   - item data read by the reader
	//       .......................
	//
	// uint16           - END_FOLDER
	////////////////////////////////////

	static const uint16 BEGIN_SUBFOLDER = 1;
	static const uint16 BEGIN_ITEM = 2;
	static const uint16 END_FOLDER = 3;

	static const uint8 HOST_ENDIANESS = 0;


	// internal globals
	extern std::function<void(MessageLevel, std::string &&)> messageCallback;

	extern void critical(std::string &&);
	extern void warning(std::string &&);
	extern void info(std::string &&);

	/**
	 * Splits a string using the passed deliminator, conditionally keeping empty entries.
	 */
	extern std::vector<std::string> split(const std::string &str, const std::string &delim, bool keepEmpty = false);
	
	/**
	 * Joins a vector of strings using glue and returns the resulting string.
	 */
	extern std::string join(const std::vector<std::string> &strings, const std::string &glue);

	/**
	 * Compares a string to another string stored in a bytestream directly in memory.  Can
	 * avoid unecessary allocations, but the stream being used must be in local memory.
	 */
	extern int strcmp(const char* left, ByteStream* stream, seek_t stringSeek);

	/**
	 * For various values in resources, the max of the datatype will indicate
	 * that the value has either not been set or is otherwise not valid.  This
	 * function provides a short hand to make code more readable when checking
	 * for that value.
	 */
	template<typename T>
	static bool varValid(const T &val)
	{
		return val != std::numeric_limits<T>::max();
	}

	/**
	 * For various values in resources, the max of the datatype will indicate
	 * that the value has either not been set or is otherwise not valid.  This
	 * function provides a short hand to make code more readable when getting
	 * that value.
	 */
	template<typename T>
	static T invalidValue()
	{
		return std::numeric_limits<T>::max();
	}

	/**
	 * For various values in resources, the max of the datatype will indicate
	 * that the value has either not been set or is otherwise not valid.  This
	 * function provides a short hand to setting a variable to that value.
	 */
	template<typename T>
	static void makeInvalid(T &var)
	{
		var = std::numeric_limits<T>::max();
	}

	/////////////////////////////////////////////////////////////////////////

	/**
	 * Autmatically stores the seek position of a stream and seeks
	 * the stream back to that position upon destruction.
	 */
	class SeekBackup
	{
		ByteStream* mStream;
		seek_t mBackSeek;
	public:
		SeekBackup(ByteStream* stream)
		{
			mStream = stream;
			mBackSeek = mStream->getSeekPosition();
		}

		~SeekBackup()
		{
			mStream->seek(mBackSeek);
		}
	};
}

#endif // _RESOURCE_INTERNAL_H_