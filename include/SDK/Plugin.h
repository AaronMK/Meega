#ifndef _MEEGA_SDK_PLUGIN_H_
#define _MEEGA_SDK_PLUGIN_H_

#include "Config.h"

#include <stdint.h>

namespace MeegaSDK
{
	class MEEGA_SDK_CLASS Plugin
	{
	public:
		Plugin();
		virtual ~Plugin();

		virtual uint32_t type() = 0;
	};
}

#endif // _MEEGA_SDK_PLUGIN_H_