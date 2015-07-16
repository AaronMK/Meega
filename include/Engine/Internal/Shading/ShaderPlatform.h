#ifndef _ENGINE_SHADER_PLATFORM_H_
#define _ENGINE_SHADER_PLATFORM_H_

#include <Engine/Config.h>

#ifdef ENGINE_API_OPEN_GL

#include <GPU/OpenGL/OpenGL.h>

namespace Engine
{

	typedef GLenum ShaderStageEnum_t;
	static const ShaderStageEnum_t ShaderVertex_v    = GL_VERTEX_SHADER;
	static const ShaderStageEnum_t ShaderTessCtrl_v  = GL_TESS_CONTROL_SHADER;
	static const ShaderStageEnum_t ShaderTessEval_v  = GL_TESS_EVALUATION_SHADER;
	static const ShaderStageEnum_t ShaderGeometry_v  = GL_GEOMETRY_SHADER;
	static const ShaderStageEnum_t ShaderFragment_v  = GL_FRAGMENT_SHADER;

	class ENGINE_DYNAMIC_CLASS ShaderPlatform
	{
	public:
		GLenum mShaderType;
		GLuint mShaderID;

	protected:
		static void move(ShaderPlatform* src, ShaderPlatform* dst);
	};
}
#else
#	error Shader is not supported on the current platform.
#endif

#endif // _ENGINE_SHADER_PLATFORM_H_
