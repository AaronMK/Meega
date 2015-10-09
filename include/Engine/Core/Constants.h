#ifndef _ENGINE_CONSTANTS_H_
#define _ENGINE_CONSTANTS_H_

#include "../Internal/Core/ConstantsPlatform.h"

namespace Engine
{
	static const double M_E         = 2.71828182845904523536;
	static const double M_LOG2E     = 1.44269504088896340736;
	static const double M_LOG10E    = 0.434294481903251827651;
	static const double M_LN2       = 0.693147180559945309417;
	static const double M_LN10      = 2.30258509299404568402;
	static const double M_PI        = 3.14159265358979323846;
	static const double M_PI_2      = 1.57079632679489661923;
	static const double M_PI_4      = 0.785398163397448309616;
	static const double M_1_PI      = 0.318309886183790671538;
	static const double M_2_PI      = 0.636619772367581343076;
	static const double M_2_SQRTPI  = 1.12837916709551257390;
	static const double M_SQRT2     = 1.41421356237309504880;
	static const double M_SQRT1_2   = 0.707106781186547524401;

	static const unsigned int COLOR_BUFFER_BIT          = COLOR_BUFFER_BIT_v;
	static const unsigned int DEPTH_BUFFER_BIT          = DEPTH_BUFFER_BIT_v;
	static const unsigned int STENCIL_BUFFER_BIT        = STENCIL_BUFFER_BIT_v;
}

#endif // _ENGINE_CONSTANTS_H_