#include <Engine/Core/Vec.h>

namespace Engine
{
	vec3::vec3()
	{
	}

	vec3::vec3(float F)
	{
		Vals[0] = Vals[1] = Vals[2] = F;
	};

	vec3::vec3(const vec3 &V3)
	{
		Vals[0] = V3.Vals[0];
		Vals[1] = V3.Vals[1];
		Vals[2] = V3.Vals[2];
	}

	vec3::vec3(float f0, float f1, float f2)
	{
		Vals[0] = f0;
		Vals[1] = f1;
		Vals[2] = f2;
	}

	vec3::vec3(const vec4 &V4)
	{
		vec4 scaledVec = V4;

		if ( V4[3] != 0 )
			scaledVec /= V4[3]; 
		
		Vals[0] = scaledVec[0];
		Vals[1] = scaledVec[1];
		Vals[2] = scaledVec[2];
	}

	vec3 vec3::operator+(const vec3 &Right) const
	{
		return vec3(Vals[0] + Right.Vals[0],
		            Vals[1] + Right.Vals[1],
		            Vals[2] + Right.Vals[2]);
	}

	void vec3::operator+=(const vec3 &Right)
	{
		Vals[0] += Right.Vals[0];
		Vals[1] += Right.Vals[1];
		Vals[2] += Right.Vals[2];
	}

	vec3 vec3::operator-(const vec3 &Right) const
	{
		return vec3(Vals[0] - Right.Vals[0],
		            Vals[1] - Right.Vals[1],
		            Vals[2] - Right.Vals[2]);
	}

	void vec3::operator-=(const vec3 &Right)
	{
		Vals[0] -= Right.Vals[0];
		Vals[1] -= Right.Vals[1];
		Vals[2] -= Right.Vals[2];
	}

	vec3 vec3::operator*(float Right) const
	{
		return vec3(Vals[0] * Right,
		            Vals[1] * Right,
		            Vals[2] * Right);
	}

	vec3 vec3::operator*(const vec3 &Right) const
	{
		return vec3(Vals[0] * Right.Vals[0],
		            Vals[1] * Right.Vals[1],
		            Vals[2] * Right.Vals[2]);
	}

	void vec3::operator*=(float Right)
	{
		Vals[0] *= Right;
		Vals[1] *= Right;
		Vals[2] *= Right;
	}

	void vec3::operator*=(const vec3 &Right)
	{
		Vals[0] *= Right.Vals[0];
		Vals[1] *= Right.Vals[1];
		Vals[2] *= Right.Vals[2];
	}

	vec3 vec3::operator/(float Right) const
	{
		// Division takes more cycles than multiplication, so calulate the
		// inverse and multiply by that instead.
		float invRight = 1.0f/Right;
		
		return vec3(Vals[0] * invRight,
		            Vals[1] * invRight,
		            Vals[2] * invRight);
	}

	vec3 vec3::operator/(const vec3 &Right) const
	{
		return vec3(Vals[0] / Right.Vals[0],
		            Vals[1] / Right.Vals[1],
		            Vals[2] / Right.Vals[2]);
	}

	void vec3::operator/=(float Right)
	{
		// Division takes more cycles than multiplication, so calulate the
		// inverse and multiply by that instead.
		float invRight = 1.0f/Right;

		Vals[0] *= invRight;
		Vals[1] *= invRight;
		Vals[2] *= invRight;
	}

	void vec3::operator/=(const vec3 &Right)
	{
		Vals[0] /= Right.Vals[0];
		Vals[1] /= Right.Vals[1];
		Vals[2] /= Right.Vals[2];
	}

	vec3 vec3::operator<(const vec3 &Right) const
	{
		// use vec4 SIMD since there is a processor op?
		
		return vec3( (Vals[0] < Right.Vals[0]) ? 1.0f : 0.0f,
		             (Vals[1] < Right.Vals[1]) ? 1.0f : 0.0f,
		             (Vals[2] < Right.Vals[2]) ? 1.0f : 0.0f);
	}

	vec3 vec3::operator<=(const vec3 &Right) const
	{
		return vec3( (Vals[0] <= Right.Vals[0]) ? 1.0f : 0.0f,
		             (Vals[1] <= Right.Vals[1]) ? 1.0f : 0.0f,
		             (Vals[2] <= Right.Vals[2]) ? 1.0f : 0.0f);
	}

	vec3 vec3::operator==(const vec3 &Right) const
	{
		return vec3( (Vals[0] == Right.Vals[0]) ? 1.0f : 0.0f,
		             (Vals[1] == Right.Vals[1]) ? 1.0f : 0.0f,
		             (Vals[2] == Right.Vals[2]) ? 1.0f : 0.0f);
	}

	vec3 vec3::operator!=(const vec3 &Right) const
	{
		return vec3( (Vals[0] != Right.Vals[0]) ? 1.0f : 0.0f,
		             (Vals[1] != Right.Vals[1]) ? 1.0f : 0.0f,
		             (Vals[2] != Right.Vals[2]) ? 1.0f : 0.0f);
	}

	vec3 vec3::operator>=(const vec3 &Right) const
	{
		return vec3( (Vals[0] >= Right.Vals[0]) ? 1.0f : 0.0f,
		             (Vals[1] >= Right.Vals[1]) ? 1.0f : 0.0f,
		             (Vals[2] >= Right.Vals[2]) ? 1.0f : 0.0f);
	}

	vec3 vec3::operator>(const vec3 &Right) const
	{
		return vec3( (Vals[0] > Right.Vals[0]) ? 1.0f : 0.0f,
		             (Vals[1] > Right.Vals[1]) ? 1.0f : 0.0f,
		             (Vals[2] > Right.Vals[2]) ? 1.0f : 0.0f);
	}

	vec3& vec3::operator=(const vec3 &Other)
	{
		Vals[0] = Other.Vals[0];
		Vals[1] = Other.Vals[1];
		Vals[2] = Other.Vals[2];

		return *this;
	}

	vec3& vec3::operator=(const vec4 &V4)
	{
		vec4 scaledVec = V4;

		if ( V4[3] != 0 )
			scaledVec /= V4[3];
		
		Vals[0] = scaledVec[0];
		Vals[1] = scaledVec[1];
		Vals[2] = scaledVec[2];

		return *this;
	}

	float& vec3::operator[](int index)
	{
		return Vals[index];
	}

	const float& vec3::operator[](int index) const
	{
		return Vals[index];
	}

	vec3::operator bool() const
	{
		return ( Vals[0] != 0.0f || Vals[1] != 0.0f || Vals[2] != 0.0f );
	}

	vec3 vec3::Min(const vec3 &F1, const vec3 &F2)
	{
		return vec3( (F1.Vals[0] < F2.Vals[0]) ? F1.Vals[0] : F2.Vals[0],
		             (F1.Vals[1] < F2.Vals[1]) ? F1.Vals[1] : F2.Vals[1],
		             (F1.Vals[2] < F2.Vals[2]) ? F1.Vals[2] : F2.Vals[2]);
	}

	vec3 vec3::Max(const vec3 &F1, const vec3 &F2)
	{
		return vec3( (F1.Vals[0] > F2.Vals[0]) ? F1.Vals[0] : F2.Vals[0],
		             (F1.Vals[1] > F2.Vals[1]) ? F1.Vals[1] : F2.Vals[1],
		             (F1.Vals[2] > F2.Vals[2]) ? F1.Vals[2] : F2.Vals[2]);
	}

	float vec3::Dot(const vec3 &F1, const vec3 &F2)
	{
		return F1[0]*F2[0] + F1[1]*F2[1] + F1[2]*F2[2];
	}

	///////////////////////////////////////

	vec4::vec4()
	{
	}

	vec4::vec4(float F)
	{
		Vals = _mm_load1_ps(&F);
	};
	
	vec4::vec4(const vec3 &V, float w)
	{
		Vals = _mm_set_ps(w, V[2], V[1], V[0]);
	}

	vec4::vec4(const vec4 &F4)
	{
		Vals = F4.Vals;
	}

	vec4::vec4(const __m128 &F)
	{
		Vals = F;
	}

	vec4::vec4(float f0, float f1, float f2, float f3)
	{
		Vals = _mm_set_ps(f3, f2, f1, f0);
	}

	vec4 vec4::operator+(const vec4 &Right) const
	{
		return _mm_add_ps(Vals, Right.Vals);
	}

	void vec4::operator+=(const vec4 &Right)
	{
		Vals = _mm_add_ps(Vals, Right.Vals);
	}

	vec4 vec4::operator-(const vec4 &Right) const
	{
		return _mm_sub_ps(Vals, Right.Vals);
	}

	void vec4::operator-=(const vec4 &Right)
	{
		Vals = _mm_sub_ps(Vals, Right.Vals);
	}

	vec4 vec4::operator*(float f) const
	{
		return _mm_mul_ps(Vals, vec4(f).Vals);
	}

	vec4 vec4::operator*(const vec4 &Right) const
	{
		return _mm_mul_ps(Vals, Right.Vals);
	}

	void vec4::operator*=(float f)
	{
		Vals = _mm_mul_ps(Vals, vec4(f).Vals);
	}

	void vec4::operator*=(const vec4 &F4)
	{
		Vals = _mm_mul_ps(Vals, F4.Vals);
	}

	vec4 vec4::operator/(float f) const
	{
		return _mm_div_ps(Vals, vec4(f).Vals);
	}

	vec4 vec4::operator/(const vec4 &Right) const
	{
		return _mm_div_ps(Vals, Right.Vals);
	}

	void vec4::operator/=(float f)
	{
		Vals = _mm_div_ps(Vals, vec4(f).Vals);
	}

	void vec4::operator/=(const vec4 &F4)
	{
		Vals = _mm_div_ps(Vals, F4.Vals);
	}

	vec4 vec4::operator<(const vec4 &Right) const
	{
		return _mm_cmplt_ps(Vals, Right.Vals);
	}

	vec4 vec4::operator<=(const vec4 &Right) const
	{
		return _mm_cmple_ps(Vals, Right.Vals);
	}

	vec4 vec4::operator==(const vec4 &Right) const
	{
		return _mm_cmpeq_ps(Vals, Right.Vals);
	}

	vec4 vec4::operator!=(const vec4 &Right) const
	{
		return _mm_cmpneq_ps(Vals, Right.Vals);
	}

	vec4 vec4::operator>=(const vec4 &Right) const
	{
		return _mm_cmpge_ps(Vals, Right.Vals);
	}

	vec4 vec4::operator>(const vec4 &Right) const
	{
		return _mm_cmpgt_ps(Vals, Right.Vals);
	}

	vec4& vec4::operator=(const vec4 &Other)
	{
		Vals = _mm_load_ps(reinterpret_cast<const float*>(&Other.Vals));
		return *this;
	}

	float& vec4::operator[](int index)
	{
		return reinterpret_cast<float*>(&Vals)[index];
	}

	const float& vec4::operator[](int index) const
	{
		return reinterpret_cast<const float*>(&Vals)[index];
	}

	vec4::operator bool() const
	{
		const float* fVals = reinterpret_cast<const float*>(&Vals);
		return ( fVals[0] != 0.0f || fVals[1] != 0.0f || fVals[2] != 0.0f || fVals[3] != 0.0f );
	}

	vec4 vec4::Min(const vec4 &F1, const vec4 &F2)
	{
		return _mm_min_ps(F1.Vals, F2.Vals); 
	}

	vec4 vec4::Max(const vec4 &F1, const vec4 &F2)
	{
		return _mm_max_ps(F1.Vals, F2.Vals); 
	}

	float vec4::Dot(const vec4 &F1, const vec4 &F2)
	{
		vec4 mult(F1*F2);
		return mult[0] + mult[1] + mult[2] + mult[3]; 
	}
}

#ifdef ENGINE_DEVEOPMENT_SUPPORT

class VecMetaType
{
public:
	VecMetaType()
	{
		qRegisterMetaType<Engine::vec3>();
		qRegisterMetaType<Engine::vec4>();
	}
};
static VecMetaType instVecMetaType;

#endif // ENGINE_DEVEOPMENT_SUPPORT