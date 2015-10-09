#ifndef _GPU_RENDER_TARGET_H_
#define _GPU_RENDER_TARGET_H_

#include "GPU.h"

#ifdef _WIN32

#include "Windows/RenderTargetWin.h"

namespace GPU
{
	typedef RenderTargetWin RenderTarget;
};

#endif // _WIN32

#endif // _GPU_RENDER_TARGET_H_