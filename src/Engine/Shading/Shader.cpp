#include <Engine/Shading/Shader.h>

#include <Engine/Core/Utility.h>
#include <Engine/Tasking/Pipeline.h>
#include <Engine/DevSupport/InterfaceHooks.h>

#include <Concurrent/Condition.h>

#include "../private_include/Tasking/GpuPipeline.h"

using namespace Concurrent;
using namespace StdExt;

namespace Engine
{
#ifdef ENGINE_API_OPEN_GL
	void ShaderPlatform::move(ShaderPlatform* src, ShaderPlatform* dst)
	{
		if (src == dst)
			return;

		if (dst->mShaderID != 0)
			Render::enqueue(std::bind(glDeleteShader, dst->mShaderID));

		dst->mShaderType = src->mShaderType;
		dst->mShaderID = src->mShaderID;

		src->mShaderType = enumVal(ShaderStage::Invalid);
		src->mShaderID = 0;
	}
	
	//////////////////////////////////////////////////////

	Shader::Shader()
	{
		mShaderType = enumVal(ShaderStage::Invalid);
		mShaderID = 0;
	}

	Shader::Shader(Shader&& other)
	{
		move(&other, this);
	}

	Shader::~Shader()
	{
		if (0 != mShaderID)
			Render::enqueue(std::bind(glDeleteShader, mShaderID));
	}

	void Shader::setSource(const std::string& source, ShaderStage stage)
	{
		setSource(StringLiteral(source.c_str()), stage);
	}

	void Shader::setSource(const String& source, ShaderStage stage)
	{
		assert(nullptr != GpuPipeline::current());

		if (0 != mShaderID)
		{
			warning(StringLiteral("Overwriting an existing shader source without a clear() action."));
			glDeleteShader(mShaderID);
		}
		else
		{
			mShaderType = enumVal(stage);
			mShaderID = glCreateShader(mShaderType);
		}

		String ntSource = source.getNullTerminated();

		const char* strings[1];
		strings[0] = ntSource.data();

		glShaderSource(mShaderID, 1, strings, NULL);
	}

	bool Shader::compile()
	{
		assert(nullptr != GpuPipeline::current());

		glCompileShader(mShaderID);

		GLint Ret;
		glGetShaderiv(mShaderID, GL_COMPILE_STATUS, &Ret);

		return GL_TRUE == Ret;
	}

	void Shader::clear()
	{
		assert(nullptr != GpuPipeline::current());

		if (0 != mShaderID)
		{
			glDeleteShader(mShaderID);

			mShaderType = enumVal(ShaderStage::Invalid);
			mShaderID = 0;
		}
	}

	Shader& Shader::operator=(Shader&& other)
	{
		move(&other, this);
		return *this;
	}
#endif
}