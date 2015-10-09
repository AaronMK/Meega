#ifndef _GPU_DIRECT_X_COMMON_H_
#define _GPU_DIRECT_X_COMMON_H_

/**
 * \file GPU/DirectX/Common.h
 * 
 * Includes and imports libraries for rewuired for the use of DirectX versions 9 - 11.
 *
 * @todo
 *  It is mentioned that DirectX 11 has profiles for previous versions.  Are the libs and
 *  headers for those versions required here?
 */

#include "../Config.h"

#if defined(GPU_SUPPORT_DIRECT_X)
#	if defined(_WIN32)
#		include <d3d11.h>
#		pragma comment (lib, "d3d11.lib")
#	else
#		error "DirectX is not supported on this platform."
#	endif
#endif

#endif // _GPU_DIRECT_X_COMMON_H_