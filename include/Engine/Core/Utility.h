#ifndef _ENGINE_UTILITY_H_
#define _ENGINE_UTILITY_H_

#include <Engine/Config.h>

#include <type_traits>
#include <algorithm>

#ifdef _WIN32
#	define ENGINE_STRICT___forceinline
#endif

namespace Engine
{
	template<typename T>
	auto enumVal(T val) -> typename std::underlying_type<T>::type
	{
		return static_cast<typename std::underlying_type<T>::type>(val);
	}

	template <typename T>
	static T clamp(T val, T min, T max)
	{
		return std::max<T>(min, std::min<T>(val, max));
	}
}

#endif // _ENGINE_UTILITY_H_