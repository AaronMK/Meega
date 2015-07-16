#include <Engine/Core/Math3d.h>

namespace Engine
{
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

	float toDegrees(float Radians)
	{
		return Radians * (180.0f * float(M_1_PI));
	}

	float toRadians(float Degrees)
	{
		return Degrees * (float(M_PI)/180.0f);
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
}