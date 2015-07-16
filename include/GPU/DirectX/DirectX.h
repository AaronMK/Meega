#ifndef _GPU_DIRECT_X_H_
#define _GPU_DIRECT_X_H_

#include <GPU/Config.h>

#ifdef GPU_SUPPORT_DIRECT_X

namespace DirectX
{
	GPU_DYNAMIC_FUNC_EXPORT bool initialize();
	GPU_DYNAMIC_FUNC_EXPORT bool shutdown();
}

#endif // GPU_SUPPORT_DIRECT_X

#endif // _GPU_DIRECT_X_H_