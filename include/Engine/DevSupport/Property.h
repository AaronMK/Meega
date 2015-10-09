#ifndef _ENGINE_PROPERTY_H_
#define _ENGINE_PROPERTY_H_

#include "../Config.h"

#include <functional>

namespace Engine
{
	template<typename T>
	class Property final
	{
	public:
		std::function<T& ()> getter;
		std::function<T& (T&&)> setter;

		operator T&() const;
		T& operator=(T&& value);
	};

	////////////////////////////////////////////////

	template<typename T>
	Property<T>::operator T&() const
	{
		return getter();
	}

	template<typename T>
	T& Property<T>::operator=(T&& value)
	{
		return setter(std::forward<T>(value));
	}
}

#endif // _ENGINE_PROPERTY_H_