#include <Engine/Core/Color.h>

#include <Engine/Core/Utility.h>

#include <cmath>

namespace Engine
{
	RGB_8::RGB_8(const RGB_F32 &color)
	{
		R = (uint8_t)(255.0f * clamp(color.R, 0.0f, 1.0f));
		G = (uint8_t)(255.0f * clamp(color.G, 0.0f, 1.0f));
		B = (uint8_t)(255.0f * clamp(color.B, 0.0f, 1.0f));
	}

	RGB_8::RGB_8(uint8_t pR, uint8_t pG, uint8_t pB)
	{
		R = pR;
		G = pG;
		B = pB;
	}

	///////////////////////////////////////

	RGBA_8::RGBA_8(const RGBA_F32 &color)
	{
		R = (uint8_t)(255.0f * clamp(color.R, 0.0f, 1.0f));
		G = (uint8_t)(255.0f * clamp(color.G, 0.0f, 1.0f));
		B = (uint8_t)(255.0f * clamp(color.B, 0.0f, 1.0f));
		A = (uint8_t)(255.0f * clamp(color.A, 0.0f, 1.0f));
	}

	RGBA_8::RGBA_8(const RGB_8 &color, uint8_t alpha)
	{
		R = color.R;
		G = color.G;
		B = color.B;
		A = alpha;
	}

	RGBA_8::RGBA_8(const RGB_F32 &color, float alpha)
	{
		R = (uint8_t)(255.0f * clamp(color.R, 0.0f, 1.0f));
		G = (uint8_t)(255.0f * clamp(color.G, 0.0f, 1.0f));
		B = (uint8_t)(255.0f * clamp(color.B, 0.0f, 1.0f));
		A = (uint8_t)(255.0f * clamp(alpha, 0.0f, 1.0f));
	}

	RGBA_8::RGBA_8(uint8_t pR, uint8_t pG, uint8_t pB, uint8_t pA)
	{
		R = pR;
		G = pG;
		B = pB;
		A = pA;
	}

	///////////////////////////////////////

	RGB_F32::RGB_F32(const RGB_8 &color)
	{
		R = (float)color.R / 255.0f;
		G = (float)color.G / 255.0f;
		B = (float)color.B / 255.0f;
	}

	RGB_F32::RGB_F32(float32_t pR, float32_t pG, float32_t pB)
	{
		R = pR;
		G = pG;
		B = pB;
	}

	///////////////////////////////////////

	RGBA_F32::RGBA_F32(const RGBA_8 &color)
	{
		R = (float)color.R / 255.0f;
		G = (float)color.G / 255.0f;
		B = (float)color.B / 255.0f;
		A = (float)color.A / 255.0f;
	}

	RGBA_F32::RGBA_F32(const RGB_8 &color, uint8_t alpha)
	{
		R = (float)color.R / 255.0f;
		G = (float)color.G / 255.0f;
		B = (float)color.B / 255.0f;
		A = (float)alpha / 255.0f;
	}

	RGBA_F32::RGBA_F32(const RGB_F32 &color, float alpha)
	{
		R = color.R;
		G = color.G;
		B = color.B;
		A = alpha;
	}

	RGBA_F32::RGBA_F32(float32_t pR, float32_t pG, float32_t pB, float32_t pA)
	{
		R = pR;
		G = pG;
		B = pB;
		A = pA;
	}

	//////////////////////////////////////////

	static float grayscale(float r, float g, float b)
	{
		return 0.2126f * r + 0.7152f * g + 0.0722f * b;
	}

	//////////////////////////////////////////

	GRAY_8::GRAY_8(const RGB_8 &color)
	{
		gray = (uint8_t)std::round(grayscale(color.R, color.G, color.B));
	}

	GRAY_8::GRAY_8(const RGB_F32 &color)
	{
		gray = (uint8_t)std::round(grayscale(color.R, color.G, color.B) * 255.0f);
	}

	GRAY_8::GRAY_8(uint8_t pG)
	{
		gray = pG;
	}

	//////////////////////////////////////////

	GRAY_F32::GRAY_F32(const RGB_8 &color)
	{
		gray = grayscale(color.R, color.G, color.B)/255.0f;
	}

	GRAY_F32::GRAY_F32(const RGB_F32 &color)
	{
		gray = grayscale(color.R, color.G, color.B);
	}

	GRAY_F32::GRAY_F32(float32_t pG)
	{
		gray = pG;
	}

	////////////////////////////////////////

	GRAY_ALPHA_8::GRAY_ALPHA_8(const RGBA_8 &color)
	{
		gray = (uint8_t)std::round(grayscale(color.R, color.G, color.B));
		alpha = (uint8_t)std::round(color.A * 255.0f);
	}

	GRAY_ALPHA_8::GRAY_ALPHA_8(const RGBA_F32 &color)
	{
		gray = (uint8_t)std::round(grayscale(color.R, color.G, color.B) * 255.0f);
		alpha = (uint8_t)std::round(color.A * 255.0f);
	}

	GRAY_ALPHA_8::GRAY_ALPHA_8(uint8_t pG, uint8_t pA)
	{
		gray = pG;
		alpha = pA;
	}

	////////////////////////////////////////

	GRAY_ALPHA_F32::GRAY_ALPHA_F32(const RGBA_8 &color)
	{
		gray = grayscale(color.R, color.G, color.B) / 255.0f;
		alpha = (float)color.A * 255.0f;
	}

	GRAY_ALPHA_F32::GRAY_ALPHA_F32(const RGBA_F32 &color)
	{
		gray = grayscale(color.R, color.G, color.B);
		alpha = color.A;
	}

	GRAY_ALPHA_F32::GRAY_ALPHA_F32(float32_t pG, float32_t pA)
	{
		gray = pG;
		alpha = pA;
	}
}