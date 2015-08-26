#include <Engine/Config.h>

namespace Engine
{
#ifdef ENGINE_DEVEOPMENT_SUPPORT
	bool DevelopmentSupport()
	{
		return true;
	}
#else
	bool DevelopmentSupport()
	{
		return false;
	}
#endif // ENGINE_DEVEOPMENT_SUPPORT

#ifdef ENGINE_DYNAMIC
	bool DynamicLibrary()
	{
		return true;
	}
#else
	bool DynamicLibrary()
	{
		return false;
	}
#endif // ENGINE_DYNAMIC
}