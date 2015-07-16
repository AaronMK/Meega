#include <GPU/Windows/RenderTargetWin.h>

namespace GPU
{
	RenderTargetWin::RenderTargetWin()
		: mPixelFormatId(0)
	{
	}

	RenderTargetWin::~RenderTargetWin()
	{
	}

	void RenderTargetWin::handleChanged()
	{
		mPixelFormatId = 0;
	}
}