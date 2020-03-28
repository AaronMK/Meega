#include <Engine/Core/Transform.h>

namespace Engine
{
	Transform::Transform()
	{
		m_Matrix = m_invMatrix = mat4x4::Identity();
	}

	Transform::Transform(const mat4x4 &mat)
	: m_Matrix(mat), m_invMatrix(m_Matrix.Inverse())
	{
	}

	Transform::Transform(const mat4x4 &mat, const mat4x4 &invMat)
	: m_Matrix(mat), m_invMatrix(invMat)
	{
	}

	Transform Transform::inverse() const
	{
		return Transform(m_invMatrix, m_Matrix);
	}

	Transform Transform::operator*(const Transform &other) const
	{
		return Transform(m_Matrix * other.m_Matrix,  other.m_invMatrix * m_invMatrix);
	}

	vec4 Transform::point(const vec3 &V) const
	{
		vec4 ret = m_Matrix * vec4(V, 1.0f);
		return ret;
	}

	vec4 Transform::point(const vec4 &V) const
	{
		assert( 0.0f != V[3] );
		
		vec4 ret = m_Matrix * V;
		return ret;
	}

	vec4 Transform::invPoint(const vec3 &V) const
	{
		vec4 ret = m_invMatrix * vec4(V, 1.0f);
		return ret;
	}

	vec4 Transform::invPoint(const vec4 &V) const
	{
		assert( 0.0f != V[3] );
		
		vec4 ret = m_invMatrix * V;
		return ret;
	}

	vec4 Transform::vector(const vec3 &V) const
	{
		return m_Matrix * vec4(V, 0.0f);
	}

	vec4 Transform::vector(const vec4 &V) const
	{
		assert( 0.0f == V[3] );
		return m_Matrix * V;
	}

	vec4 Transform::invVector(const vec3 &V) const
	{
		return m_invMatrix * vec4(V, 0.0f);
	}

	vec4 Transform::invVector(const vec4 &V) const
	{
		assert( 0.0f == V[3] );
		return m_invMatrix * V;
	}

	vec4 Transform::normal(const vec3 &V) const
	{
		vec4 ret = vec4(V) * m_invMatrix;
		ret[3] = 0.0f;
		return ret;
	}

	vec4 Transform::normal(const vec4 &V) const
	{
		assert( 0.0f == V[3] );
		
		vec4 ret = V * m_invMatrix;
		ret[3] = 0.0f;
		return ret;
	}

	vec4 Transform::invNormal(const vec3 &V) const
	{
		vec4 ret = vec4(V) * m_Matrix;
		ret[3] = 0.0f;
		return ret;
	}

	vec4 Transform::invNormal(const vec4 &V) const
	{
		assert( 0.0f == V[3] );
		
		vec4 ret = V * m_Matrix;
		ret[3] = 0.0f;
		return ret;
	}
		
	Ray4 Transform::ray(const Ray3 &R) const
	{
		return ray( Ray4(R) );
	}

	Ray4 Transform::ray(const Ray4 &R) const
	{
		Ray4 ret;

		ret.dir = m_Matrix * R.dir;
		ret.org = m_Matrix * R.org;

		return ret;
	}

	Ray4 Transform::invRay(const Ray3 &R) const
	{
		return invRay( Ray4(R) );
	}

	Ray4 Transform::invRay(const Ray4 &R) const
	{
		Ray4 ret;

		ret.dir = m_invMatrix * R.dir;
		ret.org = m_invMatrix * R.org;

		return ret;
	}

	const mat4x4& Transform::matrix() const
	{
		return m_Matrix;
	}

	const mat4x4& Transform::inverseMatrix() const
	{
		return m_invMatrix;
	}

	Transform& Transform::operator=(const mat4x4 &transMatrix)
	{
		m_Matrix = transMatrix;
		m_invMatrix = transMatrix.Inverse();

		return *this;
	}

	Transform Transform::Translate(const vec3 &tVec)
	{
		mat4x4 trans(1.0f, 0.0f, 0.0f, tVec[0],
		             0.0f, 1.0f, 0.0f, tVec[1],
		             0.0f, 0.0f, 1.0f, tVec[2],
		             0.0f, 0.0f, 0.0f, 1.0f   );
		 
		mat4x4 invTrans(1.0f, 0.0f, 0.0f, -tVec[0],
		                0.0f, 1.0f, 0.0f, -tVec[1],
		                0.0f, 0.0f, 1.0f, -tVec[2],
		                0.0f, 0.0f, 0.0f, 1.0f    );

		return Transform(trans, invTrans);
	}

	Transform Transform::Translate(float x, float y, float z)
	{
		return Translate( vec3(x, y, z) );
	}

	Transform Transform::Scale(const vec3 &sVec)
	{
		mat4x4 trans(sVec[0], 0.0f,    0.0f,    0.0f,
		             0.0f,    sVec[1], 0.0f,    0.0f,
		             0.0f,    0.0f,    sVec[2], 0.0f,
		             0.0f,    0.0f,    0.0f,    1.0f);
		 
		mat4x4 invTrans(1.0f/sVec[0], 0.0f,         0.0f,         0.0f,
		                0.0f,         1.0f/sVec[1], 0.0f,         0.0f,
		                0.0f,         0.0f,         1.0f/sVec[2], 0.0f,
		                0.0f,         0.0f,         0.0f,         1.0f);

		return Transform(trans, invTrans);
	}

	Transform Transform::Scale(float x, float y, float z)
	{
		return Scale( vec3(x, y, z) );
	}

	Transform Transform::Rotate(vec3 axis, const Radians &angle)
	{	
		vec3 a = normalize(axis);
		float s = sinf(angle.value());
		float c = cosf(angle.value());
		float m[3][3];

		m[0][0] = a[0]*a[0]*(1.0f - c) + c;
		m[0][1] = a[0]*a[1]*(1.0f - c) - a[2]*s;
		m[0][2] = a[0]*a[2]*(1.0f - c) + a[1]*s;

		m[1][0] = a[0]*a[1]*(1.0f - c) + a[2]*s;
		m[1][1] = a[1]*a[1]*(1.0f - c) + c;
		m[1][2] = a[1]*a[2]*(1.0f - c) - a[0]*s;

		m[2][0] = a[0]*a[2]*(1.0f - c) - a[1]*s;
		m[2][1] = a[1]*a[2]*(1.0f - c) + a[0]*s;
		m[2][2] = a[2]*a[2]*(1.0f - c) + c;

		mat4x4 mat( m[0][0], m[0][1], m[0][2],  0.0f,
		            m[1][0], m[1][1], m[1][2],  0.0f,
		            m[2][0], m[2][1], m[2][2],  0.0f,
		               0.0f,    0.0f,    0.0f,  1.0f);

		return Transform(mat, mat.Transpose());
	}

	Transform Transform::RasterToScreen(float winWidth, float winHeight)
	{
		return   Scale(2.0f/winWidth, -2.0f/winHeight, 1.0f)
		       * Translate(-1.0f, 1.0f, 0.0f);
	}
}


#if !defined(DOXYGEN)

namespace Serialize
{
	template<>
	void read<Engine::Transform>(ByteStream* stream, Engine::Transform *out)
	{
		Engine::mat4x4 matrix;

		read(stream, &matrix);
		*out = Engine::Transform(matrix);
	}

	template<>
	void write<Engine::Transform>(ByteStream* stream, const Engine::Transform &val)
	{
		write(stream, val.matrix());
	}
}

#endif // !defined(DOXYGEN)
