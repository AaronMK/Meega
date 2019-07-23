#ifndef _ENGINE_PROGRAM_H_
#define _ENGINE_PROGRAM_H_

#include "Shader.h"

#include "../Core/Matrix4x4.h"
#include "../Core/Color.h"

#include "../Internal/Shading/ProgramPlatform.h"

namespace Engine
{
	/**
	 * @brief
	 *  Object represents a complete shader that can be active in the pipeline.
	 *
	 *  Shaders are attached to programs
	 *  and then linked to define a complete rendering pipeline.  Programs are only valid within the context it 
	 *  is created and its shared contexts.
	 */
	class ENGINE_EXPORT Program : public ProgramPlatform
	{
	public:

		/**
		 * @brief
		 *  Makes the progam the active program.
		 */
		static void use(const Program &program);

		/**
		 * @brief
		 *  Unloads the current program.  Unloading will happen automatically
		 *  when UseProgram is called on another Program within the same context.
		 */
		static void unload();

		Program(const Program &other) = delete;
		Program& operator=(const Program &other) = delete;

		/**
		 * @brief
		 *  Creates an empty program.
		 */
		Program();

		/**
		 * @brief
		 *  Move Constructor
		 */
		Program(Program&& other);

		/**
		 * @brief
		 *  Destructor marks the program for deleteion. It will not actually be deleted
		 *  until it is no longer in use.
		 */
		virtual ~Program();

		/**
		 * @brief
		 *  Adds a shader to the program.
		 */
		bool attachShader(const Shader &S);

		/**
		 * @brief
		 *  Links a program using attached shaders.
		 */
		bool link();

		void clear();

		/**
		 * @brief
		 *  Get text describing any link errors.  This is an empty string upon succesful linking.
		 */
		StdExt::String getLinkErrors() const;

		/**
		 * @brief
		 *  Binds an attribute location to the program.
		 *
		 *  Must be called before any vertex shaders are attached to the program.
		 */
		void bindAttribLocation(GLuint index, const GLchar *name);

		GLint getAttribLocation(const char* VarName);

		/**
		 * @brief
		 *  Obtains the location of a uniform variable in a GLSL program.
		 *
		 *  The program must be successfuly linked for this function to succeed.
		 *  The returned location will be valid until the program is relinked.
		 */
		GLint getUniformLocation(const char* VarName);

		/**
		 * @brief
		 *  Obtains the location of a uniform variable in a GLSL program.
		 * 
		 *  The program must be successfuly linked for this function to succeed.
		 *  The returned location will be valid until the program is relinked.
		 */
		GLint getUniformLocation(const StdExt::String& VarName);

		void setUniform(GLint loc, int32_t val);
		void setUniform(GLint loc, float32_t val);
		void setUniform(GLint loc, const vec3 &vec);
		void setUniform(GLint loc, const vec4 &vec);
		void setUniform(GLint loc, const mat4x4 &mat);
		void setUniform(GLint loc, const RGB_F32 &color);

		/**
		 * @brief
		 *  Return the id of the program for use with OpenGL API functionality.  Use at your own risk.
		 */
		GLuint getId() const;

		Program& operator=(Program&& other);
	};
}

#endif // _ENGINE_PROGRAM_H_