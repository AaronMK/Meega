#include <Resource/Resource.h>

#include "private_include/Internal.h"

namespace Resource
{
	bool setMessageCallback(MessageCallback &&callback)
	{
		messageCallback = std::forward<MessageCallback>(callback);
	}
}