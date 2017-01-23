#include <Engine/Config.h>

namespace Engine
{
#ifdef ENGINE_DEVELOPMENT_SUPPORT
	bool DevelopmentSupport()
	{
		return true;
	}
#else
	bool DevelopmentSupport()
	{
		return false;
	}
#endif // ENGINE_DEVELOPMENT_SUPPORT

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