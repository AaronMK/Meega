#include <GPU/Config.h>

#ifdef GPU_SUPPORT_DIRECT_X

#include <GPU/DirectX/Device.h>

namespace DirectX
{
	Device::Device()
	{
	}

	Device::~Device()
	{
	}
		
	bool Device::setTarget(GPU::RenderTarget* target)
	{
		return false;
	}
}

#endif GPU_SUPPORT_DIRECT_X