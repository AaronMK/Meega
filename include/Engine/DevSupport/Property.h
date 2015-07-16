#ifndef _ENGINE_PROPERTY_H_
#define _ENGINE_PROPERTY_H_

#include <Engine/Config.h>

#include <functional>

namespace Engine
{
	/**
	 * For builds with development support, properties provided utilitles 
	 * for external tools to track and modify their values.  On non-development
	 * builds, they act like an object of type T.
	 */
	template<typename T>
	class Property final
	{
	public:

		template <typename... Args>
		Property(Args&& ...arguments);
		
		Property(T&& Value);

		~Property();

		T& operator=(T&& Value);

		operator T&();
		operator const T&();

	private:
		T mValue;

	#ifdef ENGINE_DEVEOPMENT_SUPPORT
	public:
		void setChangeHandler(std::function<void(const T&)>&& funtion);

		void setName(const std::string &name);
		
	private:
		std::function<void(const T&)> mOnChanged;
		std::string mName;

	#endif // ENGINE_DEVEOPMENT_SUPPORT
	};

	////////////////////////////////////////////////

	template<typename T>
	template <typename... Args>
	Property<T>::Property(Args&& ...arguments)
		: mValue(arguments...)
	{
	}

	template<typename T>
	Property<T>::Property(T&& value)
		: mValue(std::forward<T>(value))
	{
	}


	template<typename T>
	Property<T>::~Property()
	{

	}

	template<typename T>
	T& Property<T>::operator=(T&& Value)
	{

	}
}

#endif // _ENGINE_PROPERTY_H_