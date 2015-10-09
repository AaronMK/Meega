#ifndef _ENGINE_PROGRAM_H_
#define _ENGINE_PROGRAM_H_

#include "Shader.h"

#include "../Core/Matrix4x4.h"
#include "../Core/Color.h"

#include "../Internal/Shading/ProgramPlatform.h"

namespace Engine
{
	/**
	 * Object represents a complete shader that can be active in the pipeline.  Shaders are attached to programs
	 * and then linked to define a complete rendering pipeline.  Programs are only valid within the context it 
	 * is created and its shared contexts.
	 */
	class ENGINE_DYNAMIC_CLASS Program : public ProgramPlatform
	{
	public:
		/**
		 * Makes the progam the active program.
		 */
		static void use(const Program &program);

		/**
		 * Unloads the current program.  Unloading will happen automatically
		 * when UseProgram is called on another Program within the same context.
		 */
		static void unload();

		Program(const Program &other) = delete;
		Program& operator=(const Program &other) = delete;

		/**
		 * Creates an empty program.
		 */
		Program();

		/**
		 * Move Constructor
		 */
		Program(Program&& other);

		/**
		 * Destructor marks the program for deleteion. It will not actually be deleted
		 * until it is no longer in use.
		 */
		virtual ~Program();

		/**
		 * Adds a shader to the program.
		 */
		bool attachShader(const Shader &S);

		/**
		 * Links a program using attached shaders.
		 */
		bool link();

		void clear();

		/**
		 * Get text describing any link errors.  This is an empty string upon succesful linking.
		 */
		std::string getLinkErrors() const;

		/**
		 * Binds an attribute location to the program.  Must be called before any vertex
		 * shaders are attached to the program.
		 */
		void bindAttribLocation(GLuint index, const GLchar *name);

		GLint getAttribLocation(const char* VarName);

		/**
		 * Obtains the location of a uniform variable in a GLSL program.  The program
		 * must be successfuly linked for this function to succeed.  The returned location
		 * will be valid until the program is relinked.
		 */
		GLint getUniformLocation(const char* VarName);

		/**
		 * Obtains the location of a uniform variable in a GLSL program.  The program
		 * must be successfuly linked for this function to succeed.  The returned location
		 * will be valid until the program is relinked.
		 */
		GLint getUniformLocation(const std::string &VarName);

		void setUniform(GLint loc, int32_t val);
		void setUniform(GLint loc, float32_t val);
		void setUniform(GLint loc, const vec3 &vec);
		void setUniform(GLint loc, const vec4 &vec);
		void setUniform(GLint loc, const mat4x4 &mat);
		void setUniform(GLint loc, const RGB_F32 &color);

		/**
		 * Return the id of the program for use with OpenGL API functionality.  Use at your own risk.
		 */
		GLuint getId() const;

		Program& operator=(Program&& other);
	};
}

#endif // _ENGINE_PROGRAM_H_