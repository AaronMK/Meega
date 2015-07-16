#include <GPU/Config.h>

#if !defined(_GPU_DIRECT_X_DEVICE_H_) && defined(GPU_SUPPORT_DIRECT_X)
#define _GPU_DIRECT_X_DEVICE_H_

#include <GPU/DirectX/Common.h>
#include <GPU/RenderTarget.h>

namespace DirectX
{
	class GPU_DYNAMIC_CLASS Device
	{
	public:
		Device();
		virtual ~Device();
		
		virtual bool setTarget(GPU::RenderTarget* target);
	};
}

#endif // _GPU_DIRECT_X_DEVICE_H_