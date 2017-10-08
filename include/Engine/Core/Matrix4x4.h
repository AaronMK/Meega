#ifndef _ENGINE_MAT4_H_
#define _ENGINE_MAT4_H_

#include "Vec.h"

namespace Engine
{
	/**
	 * @brief
	 *  A 4x4 matrix class.
	 * 
	 * @details
	 *  <P>The mat4x4 class uses a column major represantation for the
	 *  following reasons:
	 *  <OL>
	 *	 <LI>It matches OpenGL's default implementation</LI>
	 *	 <LI>It can take better advantage of SSE intructions</LI>
	 *  </OL>
	 *  </P>
	 *
	 *  <P>The Rows reference makes it easier to follow code where
	 *  operations are done on a transposed matrix, but should
	 *  only be for temporary variables.</P>
	 */
	class ENGINE_EXPORT mat4x4
	{
	public:
		
		/**
		 * @brief 
		 *  Columns of the matrix
		 */
		vec4 Cols[4];
		
		/**
		 * @brief 
		 *  Creates an uninitialized matrix
		 */
		mat4x4();

		mat4x4(const mat4x4 &Other);

		mat4x4(const vec4 &C0, const vec4 &C1, const vec4 &C2, const vec4 &C3);
		
		mat4x4( float r0c0, float r0c1, float r0c2, float r0c3,
		        float r1c0, float r1c1, float r1c2, float r1c3,
		        float r2c0, float r2c1, float r2c2, float r2c3,
		        float r3c0, float r3c1, float r3c2, float r3c3);

		static mat4x4& Identity();
		
		/**
		 * @return
		 *	The transpose of the matrix.
		 */
		mat4x4 Transpose() const;

		/**
		 * @brief 
		 *  Generates a new matrix with each element the determinant of the 3x3 matrix
		 *  left when the row and column of that element are removed.
		 *
		 * @return
		 *	The generated minors matrix.
		 */
		mat4x4 Minors() const;

		/**
		 * @brief 
		 *  Generates the inverse of the matrix using Cramer's Rule.
		 * 
		 * @return
		 *	The inverse of the matrix.
		 */
		mat4x4 Inverse() const;
		
		/**
		 * @brief 
		 *  Calucalates the Trace of the matrix.  This is the sum of the elements along
		 *  the diagonal.
		 * 
		 * @return
		 *	The trace of the matrix.
		 */
		float Trace();
		
		/**
		 * @brief 
		 *  Row major access to the elements of the matrix.
		 *
		 * @param R
		 *	The row index.
		 * 
		 * @param C
		 *	The column index.
		 */
		float& RC(int R, int C);
		
		/**
		 * @brief 
		 *  Column major access to the elements of the matrix.
		 * 
		 * @param C
		 *	The column index.
		 *
		 * @param R
		 *	The row index.
		 */
		float& CR(int C, int R);

		mat4x4& operator=(const mat4x4 &Other);
		
		/**
		 * @brief 
		 *  Obtains column C from the matrix.
		 */
		vec4& operator[](int C);

		/**
		 * @brief 
		 *  Obtains column C from the matrix.
		 */
		const vec4& operator[](int C) const;
	};

	/**
	 * @brief
	 *  Multiplies the 4x4 M and the 4x1 F4, giving a 4x1 result.
	 */
	ENGINE_EXPORT vec4 operator*(const mat4x4 &M, const vec4 &F4);

	/**
	 * @brief 
	 *  Multiplies the 1x4 F4 and the 4x4 F4, giving a 1x4 result.
	 *
	 * @note
	 *  This is a SLOWER operation than (mat4x4 * vec4) since
	 *  it involves the additional calculation of a transpose.
	 */
	ENGINE_EXPORT vec4 operator*(const vec4 &F4, const mat4x4 &M);
	
	/**
	 * @brief 
	 *  Matrix multiplication.
	 */
	ENGINE_EXPORT mat4x4 operator*(const mat4x4 &M1, const mat4x4 &M2);
	
	/**
	 * @brief 
	 *  Multiplies each component of the matrix by f.
	 */
	ENGINE_EXPORT mat4x4 operator*(float f, const mat4x4 &M);
}

#if !defined(DOXYGEN)

namespace Serialize
{
	template<>
	ENGINE_EXPORT void read<Engine::mat4x4>(ByteStream* stream, Engine::mat4x4 *out);

	template<>
	ENGINE_EXPORT void write<Engine::mat4x4>(ByteStream* stream, const Engine::mat4x4 &val);
}

#if defined(ENGINE_DEVELOPMENT_SUPPORT)

#include <QtCore/QMetaType>

Q_DECLARE_METATYPE(Engine::mat4x4)

#endif // defined(ENGINE_DEVELOPMENT_SUPPORT)

#endif // !defined(DOXYGEN)

#endif // _ENGINE_MAT4_H_