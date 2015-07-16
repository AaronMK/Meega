#ifndef _ENGINE_VEC_H_
#define _ENGINE_VEC_H_

#include <Engine/Engine.h>

#include <Engine/Memory/Align16.h>

#include <Engine/Core/Utility.h>
#include <Engine/Core/SIMD.h>

namespace Engine
{
	class vec4;

	/**
	 * Abstracts SIMD floating construction and operations.
	 */
	class ENGINE_DYNAMIC_CLASS vec3
	{
	public:
		float Vals[3];

		/**
		 * Default constructor. Does not do any initialization.
		 */
		vec3();

		/**
		 * Copy Constructor.
		 */
		vec3(const vec3 &V3);

		/**
		 * Creates a vec3 with F in each of the three components.
		 */
		vec3(float F);

		/**
		 * Creates a vec3 with f0, f1, f2 as the components
		 */
		vec3(float f0, float f1, float f2);

		/**
		 * Creates a vec3 by translating from homogeneous cordinates if w is not zero.
		 */
		vec3(const vec4 &V3);

		vec3 operator+(const vec3 &Right) const;
		void operator+=(const vec3 &Right);

		vec3 operator-(const vec3 &Right) const;
		void operator-=(const vec3 &Right);

		vec3 operator*(float Right) const;
		vec3 operator*(const vec3 &Right) const;
		void operator*=(float Right);
		void operator*=(const vec3 &Right);

		vec3 operator/(float Right) const;
		vec3 operator/(const vec3 &Right) const;
		void operator/=(float Right);
		void operator/=(const vec3 &Right);

		vec3 operator<(const vec3 &Right) const;
		vec3 operator<=(const vec3 &Right) const;
		vec3 operator==(const vec3 &Right) const;
		vec3 operator!=(const vec3 &Right) const;
		vec3 operator>=(const vec3 &Right) const;
		vec3 operator>(const vec3 &Right) const;

		vec3& operator=(const vec3 &Other);
		vec3& operator=(const vec4 &V4);

		/**
		 * @return
		 *	True if any component is not equal to zero.
		 */
		operator bool() const;

		/**
		 * Provides component-wise access.
		 */
		float& operator[](int index);

		/**
		 * Provides component-wise access.
		 */
		const float& operator[](int index) const;
	
		/**
		 * Calculates the component-wise minimum of F1 and F2;
		 */
		static vec3 Min(const vec3 &F1, const vec3 &F2);

		/**
		 * Calculates the component-wise maximum of F1 and F2;
		 */
		static vec3 Max(const vec3 &F1, const vec3 &F2);

		/*
		 * Calculates the dot product.
		 */
		static float Dot(const vec3 &F1, const vec3 &F2);
	};

	/**
	 * Abstracts SIMD floating construction and operations.
	 */
	class ENGINE_DYNAMIC_CLASS vec4 : public Align16
	{
	public:
		union
		{
			__m128 Vals;
			float fVals[4];
		};

		/**
		 * Default constructor. Does not do any initialization.
		 */
		vec4();

		/**
		 * Copy Constructor.
		 */
		vec4(const vec4 &F4);

		/**
		 * Creates a vec4 with F in each of the four components.
		 */
		vec4(float F);

		/**
		 * Contructor that uses a vec3 and user provided w;
		 */
		vec4(const vec3 &V, float w = 0.0f);

		/**
		 * Creates a from the platform specific base of vec4.
		 */
		vec4(const __m128 &F);

		/**
		 * Creates a vec4 with f0, f1, f2, and f3 as the components
		 */
		vec4(float f0, float f1, float f2, float f3 = 0.0f);
		
		/**
		 * Returns the component-wise addition of this Vec4 and Right.
		 */
		vec4 operator+(const vec4 &Right) const;
		
		/**
		 * Component wise addition of Right to the Vec4.
		 */
		void operator+=(const vec4 &Right);

		vec4 operator-(const vec4 &Right) const;
		void operator-=(const vec4 &Right);

		vec4 operator*(float f) const;
		vec4 operator*(const vec4 &Right) const;
		void operator*=(float f);
		void operator*=(const vec4 &F4);

		vec4 operator/(float f) const;
		vec4 operator/(const vec4 &Right) const;
		void operator/=(float f);
		void operator/=(const vec4 &F4);

		/**
		 * Each element where this vector is less than Right will be 1.0f in the returned Vec4.
		 */
		vec4 operator<(const vec4 &Right) const;

		/**
		 * Each element where this vector is less than or equal to Right will be 1.0f in the returned Vec4.
		 */
		vec4 operator<=(const vec4 &Right) const;

		/**
		 * Each element where this vector equal to Right will be 1.0f in the returned Vec4.
		 */
		vec4 operator==(const vec4 &Right) const;
		
		/**
		 * Each element where this vector not equal to Right will be 1.0f in the returned Vec4.
		 */
		vec4 operator!=(const vec4 &Right) const;

		/**
		 * Each element where this vector is greater than or equal to Right will be 1.0f in the returned Vec4.
		 */
		vec4 operator>=(const vec4 &Right) const;

		/**
		 * Each element where this vector is greater than Right will be 1.0f in the returned Vec4.
		 */
		vec4 operator>(const vec4 &Right) const;

		/**
		 * Assignment.
		 */
		vec4& operator=(const vec4 &Other);

		/**
		 * @return
		 *	true if any component is not equal to zero.
		 */
		operator bool() const;

		/**
		 * Provides component-wise access.
		 */
		float& operator[](int index);

		/**
		 * Provides component-wise access.
		 */
		const float& operator[](int index) const;
	
		/**
		 * Calculates the component-wise minimum of F1 and F2;
		 */
		static vec4 Min(const vec4 &F1, const vec4 &F2);

		/**
		 * Calculates the component-wise maximum of F1 and F2;
		 */
		static vec4 Max(const vec4 &F1, const vec4 &F2);
		
		/*
		 * Calculates the dot product.
		 */
		static float Dot(const vec4 &F1, const vec4 &F2);
	};
}

#endif // _ENGINE_VEC_H_