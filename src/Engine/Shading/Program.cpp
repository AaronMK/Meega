#include <Engine/Shading/Program.h>

#include <Engine/Tasking/Pipeline.h>

#include <Concurrent/Condition.h>

#include "../private_include/Tasking/GpuPipeline.h"

using namespace Concurrent;

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
		assert(nullptr != GpuPipeline::current());

		if (0 == mProgramID)
			mProgramID = glCreateProgram();

		glAttachShader(mProgramID, S.mShaderID);
		return true;
	}

	bool Program::link()
	{
		assert(nullptr != GpuPipeline::current());

		glLinkProgram(mProgramID);

		GLint LinkStatus;
		glGetProgramiv(mProgramID, GL_LINK_STATUS, &LinkStatus);
		return ( GL_TRUE == LinkStatus );
	}

	void Program::clear()
	{
		assert(nullptr != GpuPipeline::current());

		if (0 != mProgramID)
		{
			glDeleteProgram(mProgramID);
			mProgramID = 0;
		}
	}

	std::string Program::getLinkErrors() const
	{
		assert(nullptr != GpuPipeline::current());

		std::string Ret;
		
		int infologLength = 0;
	    int charsWritten  = 0;
	    char *infoLog;

		glGetProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &infologLength);

	    if (infologLength > 1)
	    {
	        infoLog = (char *)malloc(infologLength);
	        glGetProgramInfoLog(mProgramID, infologLength, &charsWritten, infoLog);
			Ret = std::string(infoLog, infologLength);
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

	GLint Program::getUniformLocation(const std::string &VarName)
	{
		return glGetUniformLocation(mProgramID, VarName.c_str());
	}

	void Program::setUniform(GLint loc, int val)
	{
		glUniform1i(loc, val);
	}

	void Program::setUniform(GLint loc, float val)
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