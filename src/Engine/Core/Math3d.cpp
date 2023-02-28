#include <Engine/Core/Math3d.h>

#include <cmath>

namespace Engine
{
	Point::Point(const vec3& v3, float w) noexcept
		: vec4(v3[0], v3[1], v3[2], w)
	{
	}

	Point::Point(const vec4& v4) noexcept
		: vec4(v4)
	{
	}

	Point::Point(const Point&) noexcept = default;
	Point& Point::operator=(const Point&)  noexcept = default;

	////////////////////////////////
	
	Normal::Normal(const vec3& v3) noexcept
		: vec4(v3[0], v3[1], v3[2], 0.0f)
	{
	}

	Normal::Normal(const vec4& v4) noexcept
		: vec4(v4[0], v4[1], v4[2], 0.0f)
	{
	}

	Normal::Normal(const Normal&) noexcept = default;
	Normal& Normal::operator=(const Normal&) noexcept = default;

	void Normal::normalize()
	{
		*this = Engine::normalize(
			vec3( (*this)[0], (*this)[1], (*this)[2])
		);
	}

	////////////////////////////////
	
	Vector::Vector(const vec3& v3) noexcept
		: vec4(v3[0], v3[1], v3[2], 0.0f)
	{
	}

	Vector::Vector(const vec4& v4) noexcept
	{
		*this = ( 0.0f != v4[3] && 1.0 != v4[3] ) ?
			vec3(v4[0], v4[1], v4[2]) / v4[3] :
			vec3(v4[0], v4[1], v4[2]);
	}

	Vector::Vector(const Vector&) noexcept = default;
	Vector& Vector::operator=(const Vector&) noexcept = default;

	float Vector::length() const noexcept
	{
		return Engine::length(
			vec3((*this)[0], (*this)[1], (*this)[2])
		);
	}

	float Vector::lengthSquared() const noexcept
	{
		return Engine::lengthSquared(
			vec3((*this)[0], (*this)[1], (*this)[2])
		);
	}
	
	////////////////////////////////

	float sin(const Radians &rad)
	{
		return sinf(rad.value());
	}

	float cos(const Radians &rad)
	{
		return cosf(rad.value());
	}

	float tan(const Radians &rad)
	{
		return tanf(rad.value());
	}

	float asin(const Radians &rad)
	{
		return asinf(rad.value());
	}

	float acos(const Radians &rad)
	{
		return acosf(rad.value());
	}

	float atan(const Radians &rad)
	{
		return atanf(rad.value());
	}

	vec3 crossL(const vec3 &A, const vec3 &B)
	{
		return vec3(A[2]*B[1] - A[1]*B[2],
		            A[0]*B[2] - A[2]*B[0],
		            A[1]*B[0] - A[0]*B[1]);
	}
	
	vec3 crossR(const vec3 &A, const vec3 &B)
	{
		return vec3(A[1]*B[2] - A[2]*B[1],
		            A[2]*B[0] - A[0]*B[2],
		            A[0]*B[1] - A[1]*B[0]);
	}

	vec4 crossL(const vec4 &A, const vec4 &B)
	{
		assert( A[3] != 0.0f && B[3] != 0.0f );

		vec4 vA = A/A[3];
		vec4 vB = B/B[3];

		return   vec4(vA[2]*vB[1], vA[0]*vB[2], vA[1]*vB[0], 1.0f)
		       - vec4(vA[1]*vB[2], vA[2]*vB[0], vA[0]*vB[1], 0.0f);
	}
	
	vec4 crossR(const vec4 &A, const vec4 &B)
	{
		assert( A[3] != 0.0f && B[3] != 0.0f );

		vec4 vA = A/A[3];
		vec4 vB = B/B[3];

		return   vec4(vA[1]*vB[2], vA[2]*vB[0], vA[0]*vB[1], 1.0f)
		       - vec4(vA[2]*vB[1], vA[0]*vB[2], vA[1]*vB[0], 0.0f);
	}

	float length(const vec3 &V)
	{
		return sqrtf(lengthSquared(V));
	}

	float length(const vec4 &V)
	{
		return sqrtf(lengthSquared(V));
	}

	float lengthSquared(const vec3 &V)
	{
		return (V[0]*V[0] + V[1]*V[1] + V[2]*V[2]);
	}

	float lengthSquared(const vec4 &V)
	{
		vec4 temp(V);

		if ( 0.0f != V[3] ) 
			temp /= V[3];

		return (temp[0]*temp[0] + temp[1]*temp[1] + temp[2]*temp[2]);
	}

	vec3 normalize(const vec3 &V)
	{
		return V/length(V);
	}

	void orthonormalBasis(vec3 *Forward, vec3 *Up, vec3 *Right)
	{
		*Right = crossR(*Up, *Forward);
		*Up = crossR(*Forward, *Right);
		
		*Up = normalize(*Up);
		*Forward = normalize(*Forward);
		*Right = normalize(*Right);
	}

	void orthonormalBasis(vec4 *Forward, vec4 *Up, vec4 *Right)
	{
		assert( (*Forward)[3] != 0.0f && (*Up)[3] != 0.0f && (*Right)[3] != 0.0f );

		*Forward /= (*Forward)[3];
		*Right = crossR(*Up, *Forward);
		*Up = crossR(*Forward, *Right);
	}

	float dot(const vec3 &F1, const vec3 &F2)
	{
		return F1[0]*F2[0] + F1[1]*F2[1] + F1[2]*F2[2];
	}

	float dot(const vec4 &F1, const vec4 &F2)
	{
		vec4 mult(F1*F2);
		return mult[0] + mult[1] + mult[2] + mult[3]; 
	}

	vec3 point(const vec4& v4)
	{
		vec3 result(v4[0], v4[1], v4[2]);

		if ( 0.0f != v4[3] && 1.0 != v4[3])
			result /= v4[3];

		return result;
	}

	vec4 normal(const vec3& v3)
	{
		vec3 normalized = normalize(v3);
		return vec4(normalized[0], normalized[1], normalized[2], 0.0f);
	}

	vec3 vector(const vec4& v4)
	{
		vec3 result(v4[0], v4[1], v4[2]);

		if ( 0.0f != v4[3] && 1.0 != v4[3])
			result /= v4[3];

		return result;
	}
}