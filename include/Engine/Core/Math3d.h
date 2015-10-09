#ifndef _ENGINE_MATH_H_
#define _ENGINE_MATH_H_

#include "vec.h"
#include "Units.h"
#include "Constants.h"

#include <assert.h>


/**
 * All Math3D functions treat arguments as three-dimensional vectors.  Vec4
 * arguments are treated as homegeneous.
 *
 * @todo
 *   Homegenous functions "normalize" the vec4 (make an equivelent with w = 1).
 *   Make sure this won't cause problems and see if there are better ways to do
 *   it.
 */
namespace Engine
{
	ENGINE_FUNC_EXPORT float sin(const Radians &rad);
	ENGINE_FUNC_EXPORT float cos(const Radians &rad);
	ENGINE_FUNC_EXPORT float tan(const Radians &rad);

	ENGINE_FUNC_EXPORT float asin(const Radians &rad);
	ENGINE_FUNC_EXPORT float acos(const Radians &rad);
	ENGINE_FUNC_EXPORT float atan(const Radians &rad);

	ENGINE_FUNC_EXPORT vec3 crossL(const vec3 &A, const vec3 &B);
	ENGINE_FUNC_EXPORT vec3 crossR(const vec3 &A, const vec3 &B);

	ENGINE_FUNC_EXPORT float length(const vec3 &V);
	ENGINE_FUNC_EXPORT float length(const vec4 &V);
	
	ENGINE_FUNC_EXPORT float lengthSquared(const vec3 &V);
	ENGINE_FUNC_EXPORT float lengthSquared(const vec4 &V);

	ENGINE_FUNC_EXPORT vec3 normalize(const vec3 &V);

	ENGINE_FUNC_EXPORT void orthonormalBasis(vec3 *Forward, vec3 *Up, vec3 *Right);
	ENGINE_FUNC_EXPORT void orthonormalBasis(vec4 *Forward, vec4 *Up, vec4 *Right);
}

#endif // _ENGINE_MATH_H_