#ifndef _BASIC_SHADER_H_
#define _BASIC_SHADER_H_

#include <AppsCommon/Config.h>

#include <Engine/Memory/VertexArrayObject.h>
#include <Engine/Memory/VertexBufferObject.h>

#include <Engine/Shading/Program.h>

#include <Concurrent/Reference.h>

namespace AppsCommon
{
	class APPS_COMMON_DYNAMIC_CLASS BasicShader : public Engine::Program
	{
	public:
		BasicShader();
		virtual ~BasicShader();
	};

	class APPS_COMMON_DYNAMIC_CLASS BasicShaderParams : public Engine::VertexArrayObject
	{
	public:
		BasicShaderParams();
		virtual ~BasicShaderParams();

		Concurrent::Reference<Engine::VBO> mVertices;
		Concurrent::Reference<Engine::VBO> mColors;
	};
}

#endif // _BASIC_SHADER_H_