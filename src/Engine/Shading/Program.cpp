#include <Engine/Shading/Program.h>

#include <Engine/Tasking/Pipeline.h>

#include <StdExt/Concurrent/Condition.h>

#include "../private_include/Tasking/GpuPipeline.h"

using namespace StdExt::Concurrent;

namespace Engine
{
	void ProgramPlatform::move(ProgramPlatform* src, ProgramPlatform* dst)
	{
		if (dst->mProgramID != 0)
			Render::enqueue(std::bind(glDeleteProgram, dst->mProgramID));

		dst->mProgramID = src->mProgramID;
		src->mProgramID = 0;
	}
	
	//////////////////////////////////////////////////////

	void Program::use(const Program &program)
	{
		glUseProgram(program.mProgramID);
	}

	void Program::unload()
	{
		glUseProgram(0);
	}

	Program::Program()
		: ProgramPlatform()
	{
		mProgramID = 0;
	}

	Program::Program(Program&& other)
	{
		move(&other, this);
	}

	Program::~Program()
	{
		if (0 != mProgramID)
		{
			Render::enqueue([=]()
			{
				glDeleteProgram(mProgramID);
			});
		}
	}

	bool Program::attachShader(const Shader &S)
	{
		if (0 == mProgramID)
			mProgramID = glCreateProgram();

		glAttachShader(mProgramID, S.mShaderID);
		return true;
	}

	bool Program::link()
	{
		glLinkProgram(mProgramID);

		GLint LinkStatus;
		glGetProgramiv(mProgramID, GL_LINK_STATUS, &LinkStatus);
		return ( GL_TRUE == LinkStatus );
	}

	void Program::clear()
	{
		if (0 != mProgramID)
		{
			glDeleteProgram(mProgramID);
			mProgramID = 0;
		}
	}

	StdExt::String Program::getLinkErrors() const
	{
		StdExt::String Ret;
		
		int infologLength = 0;
		int charsWritten  = 0;
		char *infoLog;

		glGetProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &infologLength);

		if (infologLength > 1)
		{
			infoLog = (char *)malloc(infologLength);
			glGetProgramInfoLog(mProgramID, infologLength, &charsWritten, infoLog);
			Ret = StdExt::String( reinterpret_cast<const char8_t*>(infoLog), infologLength );
			free(infoLog);
		}

		return Ret;
	}

	void Program::bindAttribLocation(GLuint index, const GLchar *name)
	{
		glBindAttribLocation(mProgramID, index, name);
	}

	GLint Program::getAttribLocation(const char* VarName)
	{
		return glGetAttribLocation(mProgramID, VarName);
	}

	GLint Program::getUniformLocation(const char* VarName)
	{
		return glGetUniformLocation(mProgramID, VarName);
	}

	GLint Program::getUniformLocation(const StdExt::String& VarName)
	{
		return glGetUniformLocation(
			mProgramID,
			reinterpret_cast<const char*>(VarName.getNullTerminated().data())
		);
	}

	void Program::setUniform(GLint loc, int32_t val)
	{
		glUniform1i(loc, val);
	}

	void Program::setUniform(GLint loc, float32_t val)
	{
		glUniform1f(loc, val);
	}

	void Program::setUniform(GLint loc, const vec3 &vec)
	{
		glUniform3fv(loc, 1, &vec[0]);
	}

	void Program::setUniform(GLint loc, const vec4 &vec)
	{
		glUniform4fv(loc, 1, &vec[0]);
	}

	void Program::setUniform(GLint loc, const mat4x4 &mat)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
	}


	void Program::setUniform(GLint loc, const RGB_F32 &color)
	{
		vec3 colorvec(color.R, color.G, color.B);
		glUniform3fv(loc, 1, &colorvec[0]);
	}

	GLuint Program::getId() const
	{
		return mProgramID;
	}

	Program& Program::operator=(Program&& other)
	{
		move(&other, this);
		return *this;
	}
}