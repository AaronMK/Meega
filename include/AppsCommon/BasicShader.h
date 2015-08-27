#ifndef _BASIC_SHADER_H_
#define _BASIC_SHADER_H_

#include <AppsCommon/Config.h>

#include <Engine/Memory/VertexArrayObject.h>
#include <Engine/Memory/VertexBufferObject.h>

#include <Engine/Shading/Program.h>

#include <Engine/Core/Matrix4x4.h>
#include <Engine/Core/Color.h>

#include <Concurrent/Reference.h>

namespace AppsCommon
{
	class APPS_COMMON_DYNAMIC_CLASS BasicShader
	{
	public:
		BasicShader();
		virtual ~BasicShader();

		void setView(const Engine::mat4x4 &modelview, const Engine::mat4x4 &projection);
		void setColor(const Engine::RGB_F32 &color);

		void load();
		void unload();
	};
}

#endif // _BASIC_SHADER_H_