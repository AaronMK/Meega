#ifndef _ENGINE_RAY_H_
#define _ENGINE_RAY_H_

#include "Vec.h"

#include <limits>

namespace Engine
{
	class Ray4;

	/**
	 * @brief 
	 *  Basic ray class, suitable for simple "hit" traces.  Stores origin and
	 *  direction as vec3, so it is more space efficient but less computaionally
	 *  efficeient.
	 */
	class ENGINE_EXPORT Ray3
	{
	public:
		Ray3() = default;
		Ray3(const Ray3&) = default;

		/**
		 * @brief 
		 *  Constructs the ray, translating the other ray's origin from homogenious coordinates
		 *  if w is not 0.  For the direction, w should always be 0.
		 */
		Ray3(const Ray4 &other);

		/**
		 * @brief 
		 *  Constructs a ray with the passed origin and direction.
		 */
		Ray3(const vec3 &origin, const vec3 &direction);

		/**
		 * @brief 
		 *  Constructs the ray, translating the origin from homogenious coordinates
		 *  if w is not 0.  For the direction, w should always be 0.
		 */
		Ray3(const vec4 &origin, const vec4 &direction);

		Ray3& operator=(const Ray3&) = default;

		/**
		 * @brief 
		 *  The origin point of the ray.
		 */
		vec3 org;

		/**
		 * @brief 
		 *  The direction vector of the ray.
		 */
		vec3 dir;
	};

	/**
	 * @brief 
	 *  Basic ray class, suitable for simple "hit" traces.  Stores origin and
	 *  direction as vec4, so it is more computaionally efficient but less 
	 *  space efficeient.
	 */
	class ENGINE_EXPORT Ray4
	{
	public:
		Ray4() = default;
		Ray4(const Ray4&) = default;

		Ray4(const Ray3 &other);
		Ray4(const vec3 &origin, const vec3 &direction);
		Ray4(const vec4 &origin, const vec4 &direction);

		Ray4& operator=(const Ray4&) = default;

		/**
		 * @brief 
		 *  The origin point of the ray.
		 */
		vec4 org;

		/**
		 * @brief 
		 *  The direction vector of the ray.
		 */
		vec4 dir;
	};
}

#endif // _ENGINE_RAY_H_