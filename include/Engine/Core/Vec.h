#ifndef _ENGINE_VEC_H_
#define _ENGINE_VEC_H_

#include "Types.h"

#include <StdExt/Vec.h>

namespace Engine
{
	template class ENGINE_EXPORT StdExt::Vec2<float32_t>;
	template class ENGINE_EXPORT StdExt::Vec3<float32_t>;
	template class ENGINE_EXPORT StdExt::Vec4<float32_t>;

	using vec2 = StdExt::Vec2<float32_t>;
	using vec3 = StdExt::Vec3<float32_t>;
	using vec4 = StdExt::Vec4<float32_t>;
}

#endif //!_ENGINE_VEC_H_