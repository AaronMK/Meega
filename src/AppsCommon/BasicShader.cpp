#include <AppsCommon/BasicShader.h>

#include <AppsCommon/AppsCommon.h>
#include <Engine/Tasking/Pipeline.h>

#include <atomic>

using namespace Engine;
using namespace StdExt;

namespace AppsCommon
{
	static std::atomic<int> refCount(0);
	static Program basicProgram;
	static GLint locPosition = 0;
	static GLint locColor = 0;
	static GLint locModelView = 0;
	static GLint locProjection = 0;

	static void acquire()
	{
		QString q_vertSource(fileToString(":/AppsCommon/Shaders/basic.vert"));
		QString q_fragSource(fileToString(":/AppsCommon/Shaders/basic.frag"));

		String vertSource = convertString<char8_t>(q_vertSource.toStdString());
		String fragSource = convertString<char8_t>(q_fragSource.toStdString());

		if (0 == refCount.fetch_add(1))
		{
			Render::enqueue([vertSource, fragSource]()
			{
				Shader vertShader;
				vertShader.setSource(vertSource, ShaderStage::Vertex);
				vertShader.compile();

				Shader fragShader;
				fragShader.setSource(fragSource, ShaderStage::Fragment);
				fragShader.compile();

				basicProgram.attachShader(vertShader);
				basicProgram.attachShader(fragShader);

				basicProgram.link();

				Program::use(basicProgram);
				locPosition = basicProgram.getAttribLocation("VertexPosition");
				locColor = basicProgram.getUniformLocation("Color");
				locModelView = basicProgram.getUniformLocation("modelview");
				locProjection = basicProgram.getUniformLocation("projection");
			});
		}
	}

	static void release()
	{
		if (1 == refCount.fetch_sub(1))
		{
			Render::enqueue(std::bind(&Program::clear, &basicProgram));
		}
	}

	BasicShader::BasicShader()
	{
		acquire();
	}

	BasicShader::~BasicShader()
	{
		release();
	}

	void BasicShader::setView(const mat4x4 &modelview, const mat4x4 &projection)
	{
		basicProgram.setUniform(locModelView, modelview);
		basicProgram.setUniform(locProjection, projection);
	}

	void BasicShader::setColor(const Engine::RGB_F32 &color)
	{
		basicProgram.setUniform(locColor, color);
	}

	void BasicShader::load()
	{
		Program::use(basicProgram);
	}

	void BasicShader::unload()
	{
		Program::unload();
	}
}