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
		Quaternion(vec3 axis, float thetaRadians);

		Quaternion operator+(const Quaternion &Other) const;
		Quaternion& operator+=(const Quaternion &Other);
		Quaternion operator-(const Quaternion &Other) const;
		Quaternion& operator-=(const Quaternion &Other);
		Quaternion operator*(float f) const;
		Quaternion& operator*=(float f);
		Quaternion operator/(float f) const;
		Quaternion& operator/=(float f);

		Quaternion Normalize() const;

		/**
		 * @todo
		 *  What is this about using the transpose as the transform due to the handedness of the coordnite system?
		 */
		Transform toTransform() const;

		static float dot(const Quaternion &Q1, const Quaternion &Q2);
		static Quaternion slerp(const Quaternion &Q1, const Quaternion &Q2, float t);

	private:
		Quaternion(const vec4 &V);

		vec4 qVector;
	};

	////////////////// Implementation //////////////////
	
	Quaternion::Quaternion()
	: qVector(0.0f, 0.0f, 0.0f, 1.0f)
	{
	}

	Quaternion::Quaternion(const vec4 &V)
	: qVector(V)
	{
	}

	Quaternion::Quaternion(const Quaternion &Other)
	: qVector(Other.qVector)
	{
	}

	Quaternion::Quaternion(vec3 axis, float thetaRadians)
	{
	}

	Quaternion Quaternion::operator+(const Quaternion &Other) const
	{
		Quaternion ret(*this);
		ret.qVector += Other.qVector;
		return ret;
	}

	Quaternion& Quaternion::operator+=(const Quaternion &Other)
	{
		qVector += Other.qVector;
		return *this;
	}

	Quaternion Quaternion::operator-(const Quaternion &Other) const
	{
		Quaternion ret(*this);
		ret.qVector -= Other.qVector;
		return ret;
	}

	Quaternion& Quaternion::operator-=(const Quaternion &Other)
	{
		qVector -= Other.qVector;
		return *this;
	}

	Quaternion Quaternion::operator*(float f) const
	{
		Quaternion ret(*this);
		ret.qVector *= f;
		return ret;
	}

	Quaternion& Quaternion::operator*=(float f)
	{
		qVector *= f;
		return *this;
	}

	Quaternion Quaternion::operator/(float f) const
	{
		Quaternion ret(*this);
		ret.qVector /= f;
		return ret;
	}

	Quaternion& Quaternion::operator/=(float f)
	{
		qVector /= f;
		return *this;
	}

	Quaternion Quaternion::Normalize() const
	{
		return Quaternion( qVector/sqrtf(dot(qVector, qVector)) );
	}

	Transform Quaternion::toTransform() const
	{
		vec4 sq = qVector*qVector;
		
		float xx = sq[0], yy = sq[1], zz = sq[2];
		float xy = qVector[0]*qVector[1], xz = qVector[0]*qVector[2], yz = qVector[1]*qVector[2];
		float wx = qVector[0]*qVector[3],   wy = qVector[1]*qVector[3],   wz = qVector[2]*qVector[3];

		mat4x4 transMat( 1 - 2*(yy + zz), 2*(xy + wz), 2*(xz - wy),  0.0f,
		                 1 - 2*(xy + wz), 2*(xx + zz), 2*(yz - wx),  0.0f,
		                 1 - 2*(xz + wy), 2*(yz + wx), 2*(xx - yy),  0.0f,
		                            0.0f,        0.0f,        0.0f,  1.0f);

		return Transform(transMat, transMat.Transpose());
	}

	float Quaternion::dot(const Quaternion &Q1, const Quaternion &Q2)
	{
		return vec4::Dot(Q1.qVector, Q2.qVector);
	}

	Quaternion Quaternion::slerp(const Quaternion &Q1, const Quaternion &Q2, float t)
	{
		float cosTheta = dot(Q1, Q2);
		
		if (cosTheta > .9995f)
		{
			return (Q1*(1.0f - t) + Q2*t).Normalize();
		}
		else
		{
			float theta = acosf(clamp(cosTheta, -1.0f, 1.0f));
			float thetap = theta * t;
			Quaternion qperp = (Q2 - Q1*cosTheta).Normalize();
			return Q1 * cosf(thetap) + qperp * sinf(thetap);
		}
	}
}

#endif // _ENGINE_QUATERNION_H_