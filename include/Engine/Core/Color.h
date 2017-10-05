#ifndef _ENGINE_COLOR_H_
#define _ENGINE_COLOR_H_

#include "Types.h"

#include <Serialize/Serialize.h>

#include <cstdint>

namespace Engine
{ 
	class RGB_8;
	class RGBA_8;
	class RGB_F32;
	class RGBA_F32;
	class GRAY_8;
	class GRAY_ALPHA_8;
	class GRAY_F32;
	class GRAY_ALPHA_F32;

	enum class PixelFormat
	{
		PF_RGB_UI8,
		PF_RGBA_UI8,
		PF_RGB_F32,
		PF_RGBA_F32,
		PF_GRAY_UI8,
		PF_GRAY_ALPHA_UI8,
		PF_GRAY_F32,
		PF_GRAY_ALPHA_F32,
		UNDEFINED
	};

	//////////////////////////

	
	/**
	 * @defgroup Color Color
	 */
	
	/**
	 * @ingroup Color
	 */
	class ENGINE_EXPORT RGB_8
	{
	public:
		RGB_8() = default;

		RGB_8(const RGB_F32 &color);
		RGB_8(uint8_t pR, uint8_t pG, uint8_t pB);

		uint8_t R;
		uint8_t G;
		uint8_t B;

		static const PixelFormat Format = PixelFormat::PF_RGB_UI8;
	};

	/**
	 * @ingroup Color
	 */
	class ENGINE_EXPORT RGBA_8
	{
	public:
		RGBA_8() = default;

		RGBA_8(const RGBA_F32 &color);
		RGBA_8(const RGB_8 &color, uint8_t alpha = 255);
		RGBA_8(const RGB_F32 &color, float alpha = 1.0f);
		RGBA_8(uint8_t pR, uint8_t pG, uint8_t pB, uint8_t pA);

		uint8_t R;
		uint8_t G;
		uint8_t B;
		uint8_t A;

		static const PixelFormat Format = PixelFormat::PF_RGBA_UI8;
	};
	
	/**
	 * @ingroup Color
	 */
	class ENGINE_EXPORT RGB_F32
	{
	public:
		RGB_F32() = default;

		RGB_F32(const RGB_8 &color);
		RGB_F32(const RGBA_8 &color);
		RGB_F32(const RGBA_F32 &color);
		RGB_F32(float32_t pR, float32_t pG, float32_t pB);

		float32_t R;
		float32_t G;
		float32_t B;

		static const PixelFormat Format = PixelFormat::PF_RGB_F32;
	};
	
	/**
	 * @ingroup Color
	 */
	class ENGINE_EXPORT RGBA_F32
	{
	public:
		RGBA_F32() = default;

		RGBA_F32(const RGBA_8 &color);
		RGBA_F32(const RGB_8 &color, uint8_t alpha = 255);
		RGBA_F32(const RGB_F32 &color, float alpha = 1.0f);
		RGBA_F32(float32_t pR, float32_t pG, float32_t pB, float32_t pA);

		float32_t R;
		float32_t G;
		float32_t B;
		float32_t A;

		static const PixelFormat Format = PixelFormat::PF_RGBA_F32;
	};
	
	/**
	 * @ingroup Color
	 */
	class ENGINE_EXPORT GRAY_8
	{
	public:
		GRAY_8() = default;

		GRAY_8(const RGB_8 &color);
		GRAY_8(const RGB_F32 &color);
		GRAY_8(uint8_t pG);

		uint8_t gray;

		static const PixelFormat Format = PixelFormat::PF_GRAY_UI8;
	};
	
	/**
	 * @ingroup Color
	 */
	class ENGINE_EXPORT GRAY_F32
	{
	public:
		GRAY_F32() = default;

		GRAY_F32(const RGB_8 &color);
		GRAY_F32(const RGB_F32 &color);
		GRAY_F32(float32_t pG);

		float32_t gray;

		static const PixelFormat Format = PixelFormat::PF_GRAY_F32;
	};
	
	/**
	 * @ingroup Color
	 */
	class ENGINE_EXPORT GRAY_ALPHA_8
	{
	public:
		GRAY_ALPHA_8() = default;

		GRAY_ALPHA_8(const RGBA_8 &color);
		GRAY_ALPHA_8(const RGBA_F32 &color);
		GRAY_ALPHA_8(uint8_t pG, uint8_t pA);

		uint8_t gray;
		uint8_t alpha;

		static const PixelFormat Format = PixelFormat::PF_GRAY_ALPHA_UI8;
	};
	
	/**
	 * @ingroup Color
	 */
	class ENGINE_EXPORT GRAY_ALPHA_F32
	{
	public:
		GRAY_ALPHA_F32() = default;

		GRAY_ALPHA_F32(const RGBA_8 &color);
		GRAY_ALPHA_F32(const RGBA_F32 &color);
		GRAY_ALPHA_F32(float32_t pG, float32_t pA);

		float32_t gray;
		float32_t alpha;

		static const PixelFormat Format = PixelFormat::PF_GRAY_ALPHA_F32;
	};
}

#if !defined(DOXYGEN)

namespace Serialize
{
	template<>
	ENGINE_EXPORT void read<Engine::RGB_8>(ByteStream* stream, Engine::RGB_8 *out);

	template<>
	ENGINE_EXPORT void write<Engine::RGB_8>(ByteStream* stream, const Engine::RGB_8 &val);

	template<>
	ENGINE_EXPORT void read<Engine::RGBA_8>(ByteStream* stream, Engine::RGBA_8 *out);

	template<>
	ENGINE_EXPORT void write<Engine::RGBA_8>(ByteStream* stream, const Engine::RGBA_8 &val);

	template<>
	ENGINE_EXPORT void read<Engine::RGB_F32>(ByteStream* stream, Engine::RGB_F32 *out);

	template<>
	ENGINE_EXPORT void write<Engine::RGB_F32>(ByteStream* stream, const Engine::RGB_F32 &val);

	template<>
	ENGINE_EXPORT void read<Engine::RGBA_F32>(ByteStream* stream, Engine::RGBA_F32 *out);

	template<>
	ENGINE_EXPORT void write<Engine::RGBA_F32>(ByteStream* stream, const Engine::RGBA_F32 &val);

	template<>
	ENGINE_EXPORT void read<Engine::GRAY_8>(ByteStream* stream, Engine::GRAY_8 *out);

	template<>
	ENGINE_EXPORT void write<Engine::GRAY_8>(ByteStream* stream, const Engine::GRAY_8 &val);

	template<>
	ENGINE_EXPORT void read<Engine::GRAY_ALPHA_8>(ByteStream* stream, Engine::GRAY_ALPHA_8 *out);

	template<>
	ENGINE_EXPORT void write<Engine::GRAY_ALPHA_8>(ByteStream* stream, const Engine::GRAY_ALPHA_8 &val);

	template<>
	ENGINE_EXPORT void read<Engine::GRAY_F32>(ByteStream* stream, Engine::GRAY_F32 *out);

	template<>
	ENGINE_EXPORT void write<Engine::GRAY_F32>(ByteStream* stream, const Engine::GRAY_F32 &val);

	template<>
	ENGINE_EXPORT void read<Engine::GRAY_ALPHA_F32>(ByteStream* stream, Engine::GRAY_ALPHA_F32 *out);

	template<>
	ENGINE_EXPORT void write<Engine::GRAY_ALPHA_F32>(ByteStream* stream, const Engine::GRAY_ALPHA_F32 &val);
}

#if defined(ENGINE_DEVELOPMENT_SUPPORT)

#include <QtCore/QMetaType>

Q_DECLARE_METATYPE(Engine::RGB_8)
Q_DECLARE_METATYPE(Engine::RGBA_8)
Q_DECLARE_METATYPE(Engine::RGB_F32)
Q_DECLARE_METATYPE(Engine::RGBA_F32)
Q_DECLARE_METATYPE(Engine::GRAY_8)
Q_DECLARE_METATYPE(Engine::GRAY_ALPHA_8)
Q_DECLARE_METATYPE(Engine::GRAY_F32)
Q_DECLARE_METATYPE(Engine::GRAY_ALPHA_F32)

#endif // defined(ENGINE_DEVELOPMENT_SUPPORT)

#endif // !defined(DOXYGEN)

#endif // _ENGINE_COLOR_H_