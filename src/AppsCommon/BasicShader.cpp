#include <AppsCommon/BasicShader.h>

#include <AppsCommon/AppsCommon.h>

#include <Engine/Tasking/Pipeline.h>

using namespace Engine;

#include <atomic>

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
		QString vertSource(fileToString(":/Shaders/basic.vert"));
		QString fragSource(fileToString(":/Shaders/basic.frag"));

		if (1 == refCount.fetch_add(1))
		{
			Render::enqueue([vertSource, fragSource]()
			{
				Shader vertShader;
				vertShader.setSource(vertSource.toStdString(), ShaderStage::Vertex);
				vertShader.compile();

				Shader fragShader;
				fragShader.setSource(fragSource.toStdString(), ShaderStage::Vertex);
				fragShader.compile();

				basicProgram.attachShader(vertShader);
				basicProgram.attachShader(fragShader);

				basicProgram.link();

				locPosition = basicProgram.getAttribLocation("VertexPosition");
				locColor = basicProgram.getAttribLocation("VertexColor");
				locModelView = basicProgram.getUniformLocation("View.modelview");
				locProjection = basicProgram.getUniformLocation("View.projection");
			});
		}
	}

	static void release()
	{
		if (0 == refCount.fetch_sub(1))
		{
			Render::enqueue(std::bind(&Program::clear, &basicProgram));
			locPosition = 0;
			locColor = 0;
			locModelView = 0;
			locProjection = 0;
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

	///////////////////////////////

	BasicShaderParams::BasicShaderParams()
	{

	}

	BasicShaderParams::~BasicShaderParams()
	{

	}
}