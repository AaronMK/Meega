#ifndef _ENGINE_MAT4_H_
#define _ENGINE_MAT4_H_

#include "Vec.h"

#include <StdExt/Matrix.h>

namespace Engine
{
	template class ENGINE_EXPORT StdExt::Matrix4x4<float32_t>;
	using mat4x4 = StdExt::Matrix4x4<float32_t>;
}

#if !defined(DOXYGEN)

namespace StdExt::Serialize::Binary
{
	template<>
	ENGINE_EXPORT void read<Engine::mat4x4>(ByteStream* stream, Engine::mat4x4 *out);

	template<>
	ENGINE_EXPORT void write<Engine::mat4x4>(ByteStream* stream, const Engine::mat4x4 &val);
}

#endif // !defined(DOXYGEN)

#endif // _ENGINE_MAT4_H_