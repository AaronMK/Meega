#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Config.h"
#include "Options.h"

namespace Engine
{
	ENGINE_EXPORT bool initialize();
	ENGINE_EXPORT void shutdown();
}

#endif // _ENGINE_H_