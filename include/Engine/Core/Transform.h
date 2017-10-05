#ifndef _ENGINE_TRANSFORM_H_
#define _ENGINE_TRANSFORM_H_

#include "Matrix4x4.h"
#include "Math3d.h"
#include "Units.h"
#include "Ray.h"

#include <math.h>
#include <assert.h>

namespace Engine
{
	/**
	 * @brief
	 *  Transform class stores a transformation matrix and its inverse.
	 *
	 *  It provides static functions for creating common transforms, and applying the transform to 
	 *  points, vectors, and normals.  All vec3 forms transform function return vec4 since if that type 
	 *  is not passed, it will be created to perform perform the transform.  It might as well be 
	 *  kept to speed further operations and to maintain the w value, see utility functions for getting
	 *  the vec3 back.
	 *
	 *  Transforms can be stacked using the multiplication operator.  The left-to-right order of the transformations
	 *  is the order in which the matrices will be multiplied.  The most local transforms to the should be on
	 *  the right.
	 */
	class ENGINE_EXPORT Transform : public Align16
	{
	public:
		Transform();
		Transform(const mat4x4 &mat);
		Transform(const mat4x4 &mat, const mat4x4 &invMat);

		Transform inverse() const;
		Transform operator*(const Transform &other) const;

		vec4 point(const vec3 &V) const;
		vec4 point(const vec4 &V) const;

		vec4 invPoint(const vec3 &V) const;
		vec4 invPoint(const vec4 &V) const;

		vec4 vector(const vec3 &V) const;
		vec4 vector(const vec4 &V) const;

		vec4 invVector(const vec3 &V) const;
		vec4 invVector(const vec4 &V) const;

		vec4 normal(const vec3 &V) const;
		vec4 normal(const vec4 &V) const;

		vec4 invNormal(const vec3 &V) const;
		vec4 invNormal(const vec4 &V) const;
		
		Ray4 ray(const Ray3 &R) const;
		Ray4 ray(const Ray4 &R) const;

		Ray4 invRay(const Ray3 &R) const;
		Ray4 invRay(const Ray4 &R) const;

		const mat4x4& matrix() const;
		const mat4x4& inverseMatrix() const;

		Transform& operator=(const mat4x4 &transMatrix);

		static Transform Translate(const vec3 &tVec);
		static Transform Translate(float x, float y, float z);

		static Transform Scale(const vec3 &sVec);
		static Transform Scale(float x, float y, float z);
		
		static Transform Rotate(vec3 axis, const Radians &angle);

		/**
		 * @brief 
		 *  Creates a transform that can be used to convert screen coordanites starting with (0, 0)
		 *  at the top-left to Normalized Device Coordinates [-1, 1] in x and y.
		 */
		static Transform RasterToScreen(float winWidth, float winHeight);

	private:
		mat4x4 m_Matrix;
		mat4x4 m_invMatrix;
	};
}

#if !defined(DOXYGEN)

namespace Serialize
{
	template<>
	ENGINE_EXPORT void read<Engine::Transform>(ByteStream* stream, Engine::Transform *out);

	template<>
	ENGINE_EXPORT void write<Engine::Transform>(ByteStream* stream, const Engine::Transform &val);
}

#if defined(ENGINE_DEVELOPMENT_SUPPORT)

#include <QtCore/QMetaType>

Q_DECLARE_METATYPE(Engine::Transform)

#endif // defined(ENGINE_DEVELOPMENT_SUPPORT)

#endif // !defined(DOXYGEN)

#endif // _ENGINE_TRANSFORM_H_