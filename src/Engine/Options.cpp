#include <Engine/Options.h>

#include <cstddef>

namespace Engine
{
	Options::Options()
	{
		interfaceHooks = NULL;
		mainRenderTarget = NULL;
		vSync = VSync::AUTO;

#		ifdef ENGINE_DEVEOPMENT_SUPPORT
			debug = true;
#		else
			debug = false;
#		endif
	}
}