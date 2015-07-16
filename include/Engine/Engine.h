#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <Engine/Config.h>
#include <Engine/Options.h>

namespace Engine
{
	ENGINE_FUNC_EXPORT bool initialize();
	ENGINE_FUNC_EXPORT void shutdown();
}

#endif // _ENGINE_H_