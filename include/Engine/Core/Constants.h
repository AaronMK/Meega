#ifndef _ENGINE_CONSTANTS_H_
#define _ENGINE_CONSTANTS_H_

#include "../Internal/Core/ConstantsPlatform.h"

#undef M_E
#undef M_LOG2E
#undef M_LOG10E
#undef M_LN2
#undef M_LN10
#undef M_PI
#undef M_PI_2
#undef M_PI_4
#undef M_1_PI
#undef M_2_PI
#undef M_2_SQRTPI
#undef M_SQRT2
#undef M_SQRT1_2

namespace Engine
{
	constexpr double M_E         = 2.71828182845904523536;
	constexpr double M_LOG2E     = 1.44269504088896340736;
	constexpr double M_LOG10E    = 0.434294481903251827651;
	constexpr double M_LN2       = 0.693147180559945309417;
	constexpr double M_LN10      = 2.30258509299404568402;
	constexpr double M_PI        = 3.14159265358979323846;
	constexpr double M_PI_2      = 1.57079632679489661923;
	constexpr double M_PI_4      = 0.785398163397448309616;
	constexpr double M_1_PI      = 0.318309886183790671538;
	constexpr double M_2_PI      = 0.636619772367581343076;
	constexpr double M_2_SQRTPI  = 1.12837916709551257390;
	constexpr double M_SQRT2     = 1.41421356237309504880;
	constexpr double M_SQRT1_2   = 0.707106781186547524401;
	
	constexpr unsigned int COLOR_BUFFER_BIT          = COLOR_BUFFER_BIT_v;
	constexpr unsigned int DEPTH_BUFFER_BIT          = DEPTH_BUFFER_BIT_v;
	constexpr unsigned int STENCIL_BUFFER_BIT        = STENCIL_BUFFER_BIT_v;
}

#endif // _ENGINE_CONSTANTS_H_