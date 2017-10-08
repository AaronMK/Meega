#ifndef _ENGINE_QUATERNION_H_
#define _ENGINE_QUATERNION_H_

#include "../Core/Transform.h"
#include "../Core/Matrix4x4.h"
#include "../Core/Utility.h"
#include "../Core/Units.h"
#include "../Core/Vec.h"

namespace Engine
{
	/**
	 * @brief
	 *	%Quaternion class.
	 */
	class ENGINE_EXPORT Quaternion
	{
	public:
		Quaternion() = default;
		Quaternion(const Quaternion&) = default;
		Quaternion& operator=(const Quaternion&) = default;

		Quaternion(const vec3 &v, float w = 1.0);
		Quaternion(float x, float y, float z, float w = 1.0);

		static Quaternion fromAngle(const vec3 &v, const Radians &r);
		static Quaternion fromAngle(float x, float y, float z, const Radians &r);

		Quaternion operator+(const Quaternion &Other) const;
		Quaternion& operator+=(const Quaternion &Other);
		Quaternion operator-(const Quaternion &Other) const;
		Quaternion& operator-=(const Quaternion &Other);
		Quaternion operator*(float f) const;
		Quaternion& operator*=(float f);
		Quaternion operator/(float f) const;
		Quaternion& operator/=(float f);

		Quaternion normalize() const;

		Transform toTransform() const;

		static float dot(const Quaternion &Q1, const Quaternion &Q2);
		static Quaternion slerp(const Quaternion &Q1, const Quaternion &Q2, float t);

	private:
		vec3 mVec;
		float mW;
	};
}

#endif // _ENGINE_QUATERNION_H_