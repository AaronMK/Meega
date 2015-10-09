#include <Engine/Core/Quaternion.h>

#include <Engine/Core/Math3d.h>

namespace Engine
{
	Quaternion::Quaternion(const vec3 &v, float w)
		: mVec(v), mW(w)
	{
	}

	Quaternion::Quaternion(float x, float y, float z, float w)
		: Quaternion(vec3(x, y, z), w)
	{

	}

	Quaternion Quaternion::fromAngle(const vec3 &v, const Radians &r)
	{
		Quaternion ret;

		ret.mVec = v;
		ret.mW = ::cos(r.value() / 2.0f);

		return ret;
	}

	Quaternion Quaternion::fromAngle(float x, float y, float z, const Radians &r)
	{
		return fromAngle(vec3(x, y, z), r);
	}

	Quaternion Quaternion::operator+(const Quaternion &Other) const
	{
		Quaternion ret(*this);
		ret.mVec += Other.mVec;
		ret.mW += Other.mW;
		return ret;
	}

	Quaternion& Quaternion::operator+=(const Quaternion &Other)
	{
		mVec += Other.mVec;
		mW += Other.mW;
		return *this;
	}

	Quaternion Quaternion::operator-(const Quaternion &Other) const
	{
		Quaternion ret(*this);
		ret.mVec -= Other.mVec;
		ret.mW -= Other.mW;
		return ret;
	}

	Quaternion& Quaternion::operator-=(const Quaternion &Other)
	{
		mVec -= Other.mVec;
		mW -= Other.mW;
		return *this;
	}

	Quaternion Quaternion::operator*(float f) const
	{
		Quaternion ret(*this);
		ret.mVec *= f;
		ret.mW *= f;
		return ret;
	}

	Quaternion& Quaternion::operator*=(float f)
	{
		mVec *= f;
		mW *= f;
		return *this;
	}

	Quaternion Quaternion::operator/(float f) const
	{
		Quaternion ret(*this);
		ret.mVec /= f;
		ret.mW /= f;
		return ret;
	}

	Quaternion& Quaternion::operator/=(float f)
	{
		mVec /= f;
		mW /= f;
		return *this;
	}

	Quaternion Quaternion::normalize() const
	{
		return *this / sqrtf(dot(mVec, mVec));
	}

	Transform Quaternion::toTransform() const
	{
		vec4 sq = mVec*mVec;

		float xx = sq[0], yy = sq[1], zz = sq[2];
		float xy = mVec[0] * mVec[1], xz = mVec[0] * mVec[2], yz = mVec[1] * mVec[2];
		float wx = mVec[0] * mVec[3], wy = mVec[1] * mVec[3], wz = mVec[2] * mVec[3];

		mat4x4 transMat(1 - 2 * (yy + zz), 2 * (xy + wz), 2 * (xz - wy), 0.0f,
		                1 - 2 * (xy + wz), 2 * (xx + zz), 2 * (yz - wx), 0.0f,
		                1 - 2 * (xz + wy), 2 * (yz + wx), 2 * (xx - yy), 0.0f,
		                0.0f,              0.0f,          0.0f,          1.0f);

		return Transform(transMat, transMat.Transpose());
	}

	float Quaternion::dot(const Quaternion &Q1, const Quaternion &Q2)
	{
		return vec3::Dot(Q1.mVec, Q2.mVec) + Q1.mW * Q2.mW;
	}

	Quaternion Quaternion::slerp(const Quaternion &Q1, const Quaternion &Q2, float t)
	{
		float cosTheta = dot(Q1, Q2);

		if (cosTheta > .9995f)
		{
			return (Q1*(1.0f - t) + Q2*t).normalize();
		}
		else
		{
			float theta = acosf(clamp(cosTheta, -1.0f, 1.0f));
			float thetap = theta * t;
			Quaternion qperp = (Q2 - Q1*cosTheta).normalize();
			return Q1 * cosf(thetap) + qperp * sinf(thetap);
		}
	}
}