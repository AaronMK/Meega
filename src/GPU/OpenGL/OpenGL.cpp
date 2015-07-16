#include <GPU/OpenGL/OpenGL.h>

#include <GPU/OpenGL/Context.h>

#include "../private_include/Windows/HiddenWindow.h"

#include <sstream>
#include <string>
#include <mutex>

namespace OpenGL
{
	static int maxGLVersionMajor = -1;
	static int maxGLVersionMinor = -1;

	static int maxGLSLVersionMajor = -1;
	static int maxGLSLVersionMinor = -1;

	static std::string vendorString;
	static std::string rendererString;

	bool initialize()
	{
		GPU::HiddenWindow::initialize();

		Format testFmnt;
		testFmnt.versionMajor = 2;
		testFmnt.versionMinor = 1;
		testFmnt.versionProfile = Profile::COMPATIBILITY;

		Context* testCtxt = new Context(testFmnt);

		testCtxt->makeCurrent();
		vendorString = std::string((char*)glGetString(GL_VENDOR));
		rendererString = std::string((char*)glGetString(GL_RENDERER));
		std::string versionString((char*)glGetString(GL_VERSION));
		std::string glslVersionString((char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
		testCtxt->doneCurrent();

		delete testCtxt;

		std::stringstream strStream(versionString);
		std::string token;

		std::getline(strStream, token, '.');
		maxGLVersionMajor = atoi(token.c_str());
		std::getline(strStream, token, '.');
		maxGLVersionMinor = atoi(token.c_str());

		return true;
	}

	bool shutdown()
	{
		maxGLVersionMajor = -1;
		maxGLVersionMinor = -1;

		maxGLSLVersionMajor = -1;
		maxGLSLVersionMinor = -1;

		vendorString.clear();
		rendererString.clear();

		GPU::HiddenWindow::shutdown();

		return true;
	}

	void maxGLVersion(int* outMajor, int *outMinor)
	{
		*outMajor = maxGLVersionMajor;
		*outMinor = maxGLVersionMinor;
	}

	const std::string& getGLVendorString()
	{
		return vendorString;
	}

	const std::string& getGLRendererString()
	{
		return rendererString;
	}

	const char* getLastError()
	{
		static char* nullString = "";

		GLenum errCode = glGetError();
		if ( errCode != GL_NO_ERROR )
		{
			const GLubyte *errString = gluErrorString(errCode);
			return (char*)errString;
		}

		return nullString;
	}
}