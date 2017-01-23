#include <Engine/Core/Matrix4x4.h>

namespace Engine
{
	mat4x4::mat4x4()
	{
	}

	mat4x4::mat4x4(const mat4x4 &Other)
	{
		Cols[0] = Other.Cols[0];
		Cols[1] = Other.Cols[1];
		Cols[2] = Other.Cols[2];
		Cols[3] = Other.Cols[3];
	}

	mat4x4::mat4x4(const vec4 &C0, const vec4 &C1, const vec4 &C2, const vec4 &C3)
	{
		Cols[0] = C0;
		Cols[1] = C1;
		Cols[2] = C2;
		Cols[3] = C3;
	}

	mat4x4::mat4x4(float r0c0, float r0c1, float r0c2, float r0c3,
	               float r1c0, float r1c1, float r1c2, float r1c3,
	               float r2c0, float r2c1, float r2c2, float r2c3,
	               float r3c0, float r3c1, float r3c2, float r3c3)
	{
		Cols[0][0] = r0c0; Cols[1][0] = r0c1; Cols[2][0] = r0c2; Cols[3][0] = r0c3;
		Cols[0][1] = r1c0; Cols[1][1] = r1c1; Cols[2][1] = r1c2; Cols[3][1] = r1c3;
		Cols[0][2] = r2c0; Cols[1][2] = r2c1; Cols[2][2] = r2c2; Cols[3][2] = r2c3;
		Cols[0][3] = r3c0; Cols[1][3] = r3c1; Cols[2][3] = r3c2; Cols[3][3] = r3c3;
	}

	mat4x4& mat4x4::Identity()
	{
		static mat4x4 ident(1.0f, 0.0f, 0.0f, 0.0f,
		                    0.0f, 1.0f, 0.0f, 0.0f,
		                    0.0f, 0.0f, 1.0f, 0.0f,
		                    0.0f, 0.0f, 0.0f, 1.0f);

		return ident;
	}

	mat4x4 mat4x4::Transpose() const
	{
		mat4x4 Tmp;
		mat4x4 Ret;

		Tmp.Cols[0] = MMShuffle(Cols[0], Cols[1], ShuffleMask(0,1,0,1));
		Tmp.Cols[2] = MMShuffle(Cols[0], Cols[1], ShuffleMask(2,3,2,3));
		Tmp.Cols[1] = MMShuffle(Cols[2], Cols[3], ShuffleMask(0,1,0,1));
		Tmp.Cols[3] = MMShuffle(Cols[2], Cols[3], ShuffleMask(2,3,2,3));

		Ret.Cols[0] = MMShuffle(Tmp.Cols[0], Tmp.Cols[1], ShuffleMask(0,2,0,2));
		Ret.Cols[1] = MMShuffle(Tmp.Cols[0], Tmp.Cols[1], ShuffleMask(1,3,1,3));
		Ret.Cols[2] = MMShuffle(Tmp.Cols[2], Tmp.Cols[3], ShuffleMask(0,2,0,2));
		Ret.Cols[3] = MMShuffle(Tmp.Cols[2], Tmp.Cols[3], ShuffleMask(1,3,1,3));

		return Ret;
	}

	mat4x4 mat4x4::Minors() const
	{
		mat4x4 Ret;
		vec4 C1C2;

		// The first column
		C1C2 = Cols[1]*MMShuffle(Cols[2], Cols[2], ShuffleMask(1,2,3,0));

		Ret.Cols[0] = MMShuffle(C1C2, C1C2, ShuffleMask(1,2,3,0))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(3,0,1,2));

		Ret.Cols[0] += MMShuffle(C1C2, C1C2, ShuffleMask(2,3,0,1))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(1,2,3,0));

		Ret.Cols[0] += MMShuffle(Cols[1], Cols[1], ShuffleMask(3,0,1,2))
			* MMShuffle(Cols[2], Cols[2], ShuffleMask(1,2,3,0))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(2,3,0,1));

		C1C2 = Cols[1]*MMShuffle(Cols[2], Cols[2], ShuffleMask(3,0,1,2));

		Ret.Cols[0] -= MMShuffle(C1C2, C1C2, ShuffleMask(3,0,1,2))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(1,2,3,0));

		Ret.Cols[0] -= MMShuffle(C1C2, C1C2, ShuffleMask(2,3,0,1))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(3,0,1,2));

		Ret.Cols[0] -= MMShuffle(Cols[1], Cols[1], ShuffleMask(1,2,3,0))
			* MMShuffle(Cols[2], Cols[2], ShuffleMask(3,0,1,2))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(2,3,0,1));


		// The Second Column
		C1C2 = Cols[0]*MMShuffle(Cols[2], Cols[2], ShuffleMask(1,2,3,0));

		Ret.Cols[1] = MMShuffle(C1C2, C1C2, ShuffleMask(1,2,3,0))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(3,0,1,2));

		Ret.Cols[1] += MMShuffle(C1C2, C1C2, ShuffleMask(2,3,0,1))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(1,2,3,0));

		Ret.Cols[1] += MMShuffle(Cols[0], Cols[0], ShuffleMask(3,0,1,2))
			* MMShuffle(Cols[2], Cols[2], ShuffleMask(1,2,3,0))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(2,3,0,1));

		C1C2 = Cols[0]*MMShuffle(Cols[2], Cols[2], ShuffleMask(3,0,1,2));

		Ret.Cols[1] -= MMShuffle(C1C2, C1C2, ShuffleMask(3,0,1,2))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(1,2,3,0));

		Ret.Cols[1] -= MMShuffle(C1C2, C1C2, ShuffleMask(2,3,0,1))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(3,0,1,2));

		Ret.Cols[1] -= MMShuffle(Cols[0], Cols[0], ShuffleMask(1,2,3,0))
			* MMShuffle(Cols[2], Cols[2], ShuffleMask(3,0,1,2))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(2,3,0,1));


		// The Third Column
		C1C2 = Cols[0]*MMShuffle(Cols[1], Cols[1], ShuffleMask(1,2,3,0));

		Ret.Cols[2] = MMShuffle(C1C2, C1C2, ShuffleMask(1,2,3,0))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(3,0,1,2));

		Ret.Cols[2] += MMShuffle(C1C2, C1C2, ShuffleMask(2,3,0,1))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(1,2,3,0));

		Ret.Cols[2] += MMShuffle(Cols[0], Cols[0], ShuffleMask(3,0,1,2))
			* MMShuffle(Cols[1], Cols[1], ShuffleMask(1,2,3,0))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(2,3,0,1));

		C1C2 = Cols[0]*MMShuffle(Cols[1], Cols[1], ShuffleMask(3,0,1,2));

		Ret.Cols[2] -= MMShuffle(C1C2, C1C2, ShuffleMask(3,0,1,2))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(1,2,3,0));

		Ret.Cols[2] -= MMShuffle(C1C2, C1C2, ShuffleMask(2,3,0,1))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(3,0,1,2));

		Ret.Cols[2] -= MMShuffle(Cols[0], Cols[0], ShuffleMask(1,2,3,0))
			* MMShuffle(Cols[1], Cols[1], ShuffleMask(3,0,1,2))
			* MMShuffle(Cols[3], Cols[3], ShuffleMask(2,3,0,1));

		// The Fourth Column
		C1C2 = Cols[0]*MMShuffle(Cols[1], Cols[1], ShuffleMask(1,2,3,0));

		Ret.Cols[3] = MMShuffle(C1C2, C1C2, ShuffleMask(1,2,3,0))
			* MMShuffle(Cols[2], Cols[2], ShuffleMask(3,0,1,2));

		Ret.Cols[3] += MMShuffle(C1C2, C1C2, ShuffleMask(2,3,0,1))
			* MMShuffle(Cols[2], Cols[2], ShuffleMask(1,2,3,0));

		Ret.Cols[3] += MMShuffle(Cols[0], Cols[0], ShuffleMask(3,0,1,2))
			* MMShuffle(Cols[1], Cols[1], ShuffleMask(1,2,3,0))
			* MMShuffle(Cols[2], Cols[2], ShuffleMask(2,3,0,1));

		C1C2 = Cols[0]*MMShuffle(Cols[1], Cols[1], ShuffleMask(3,0,1,2));

		Ret.Cols[3] -= MMShuffle(C1C2, C1C2, ShuffleMask(3,0,1,2))
			* MMShuffle(Cols[2], Cols[2], ShuffleMask(1,2,3,0));

		Ret.Cols[3] -= MMShuffle(C1C2, C1C2, ShuffleMask(2,3,0,1))
			* MMShuffle(Cols[2], Cols[2], ShuffleMask(3,0,1,2));

		Ret.Cols[3] -= MMShuffle(Cols[0], Cols[0], ShuffleMask(1,2,3,0))
			* MMShuffle(Cols[1], Cols[1], ShuffleMask(3,0,1,2))
			* MMShuffle(Cols[2], Cols[2], ShuffleMask(2,3,0,1));

		return Ret;
	}

	mat4x4 mat4x4::Inverse() const
	{
		static const vec4 pnpn(1.0f,-1.0f,1.0f,-1.0f);
		static const vec4 npnp(-1.0f,1.0f,-1.0f,1.0f);

		mat4x4 C = Minors();

		// Cofactors
		C.Cols[0] *= pnpn;
		C.Cols[1] *= npnp;
		C.Cols[2] *= pnpn;
		C.Cols[3] *= npnp;

		vec4 Temp = Cols[0]*C.Cols[0];

		float Det = Temp[0] + Temp[1] + Temp[2] + Temp[3];

		return (1.0f/Det)*C.Transpose();
	}

	float mat4x4::Trace()
	{
		return Cols[0][0] + Cols[1][1] + Cols[2][2] + Cols[3][3];
	}

	float& mat4x4::RC(int R, int C)
	{
		return Cols[C][R];
	}


	float& mat4x4::CR(int C, int R)
	{
		return Cols[C][R];
	}

	mat4x4& mat4x4::operator=(const mat4x4 &Other)
	{
		Cols[0] = Other.Cols[0];
		Cols[1] = Other.Cols[1];
		Cols[2] = Other.Cols[2];
		Cols[3] = Other.Cols[3];

		return *this;
	}
	
	vec4& mat4x4::operator[](int C)
	{
		return Cols[C];
	}

	const vec4& mat4x4::operator[](int C)  const
	{
		return Cols[C];
	}

	vec4 operator*(const mat4x4 &M, const vec4 &F4)
	{
		return   M.Cols[0]*F4[0]
		       + M.Cols[1]*F4[1]
		       + M.Cols[2]*F4[2]
		       + M.Cols[3]*F4[3];
	}

	vec4 operator*(const vec4 &F4, const mat4x4 &M)
	{
		mat4x4 transposeM = M.Transpose();
		
		return   transposeM.Cols[0]*F4[0]
		       + transposeM.Cols[1]*F4[1]
		       + transposeM.Cols[2]*F4[2]
		       + transposeM.Cols[3]*F4[3];
	}

	mat4x4 operator*(const mat4x4 &M1, const mat4x4 &M2)
	{
		return mat4x4(M1*M2.Cols[0],
		              M1*M2.Cols[1],
		              M1*M2.Cols[2],
		              M1*M2.Cols[3]);
	}

	mat4x4 operator*(float f, const mat4x4 &M)
	{
		vec4 Mult(f);

		return mat4x4(Mult*M.Cols[0],
		              Mult*M.Cols[1],
		              Mult*M.Cols[2],
		              Mult*M.Cols[3]);
	}
}

#if defined(ENGINE_DEVELOPMENT_SUPPORT) && !defined(DOXYGEN)

class Mat4x4MetaType
{
public:
	Mat4x4MetaType()
	{
		qRegisterMetaType<Engine::mat4x4>();
	}
};
static Mat4x4MetaType instMat4x4MetaType;

#endif // defined(ENGINE_DEVELOPMENT_SUPPORT) && !defined(DOXYGEN)
