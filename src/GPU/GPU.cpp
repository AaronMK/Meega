#include <GPU/GPU.h>

namespace GPU
{
	bool supportsDirectX()
	{
		#if defined(GPU_SUPPORT_DIRECT_X)
			return true;
		#else
			return false:
		#endif
	}
	
	bool supportsOpenGL()
	{
		#if defined(GPU_SUPPORT_OPEN_GL)
			return true;
		#else
			return false:
		#endif
	}

	bool isDynamic()
	{
		#if defined(GPU_DYNAMIC_LIB)
			return true;
		#else
			return false:
		#endif
	}
}