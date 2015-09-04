#ifndef _ENGINE_QUATERNION_H_
#define _ENGINE_QUATERNION_H_

#include <Engine/Memory/Align16.h>

#include <Engine/Core/Transform.h>
#include <Engine/Core/Matrix4x4.h>
#include <Engine/Core/Utility.h>
#include <Engine/Core/vec.h>

namespace Engine
{
	/**
	 * Quaternion class.
	 */
	class Quaternion : public Align16
	{
	public:
		Quaternion();
		Quaternion(const Quaternion &Q);
		Quaternion(const vec3 &v, float w = 1.0);

		Quaternion operator+(const Quaternion &Other) const;
		Quaternion& operator+=(const Quaternion &Other);
		Quaternion operator-(const Quaternion &Other) const;
		Quaternion& operator-=(const Quaternion &Other);
		Quaternion operator*(float f) const;
		Quaternion& operator*=(float f);
		Quaternion operator/(float f) const;
		Quaternion& operator/=(float f);

		Quaternion normalize() const;

		/**
		 * @todo
		 *  What is this about using the transpose as the transform due to the handedness of the coordnite system?
		 */
		Transform toTransform() const;

		static float dot(const Quaternion &Q1, const Quaternion &Q2);
		static Quaternion slerp(const Quaternion &Q1, const Quaternion &Q2, float t);

	private:
		vec3 mVec;
		float mW;
	};
}

#endif // _ENGINE_QUATERNION_H_