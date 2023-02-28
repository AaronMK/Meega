#include "../private_include/Tasking/GpuPipeline.h"

#include <Engine/DevSupport/Logging.h>
#include <Engine/Tasking/Pipeline.h>

#include "../private_include/Debug/DebugGL.h"

#include <limits>
#include <sstream>

using namespace StdExt;

namespace Engine
{
#ifdef ENGINE_API_OPEN_GL
#	ifdef ENGINE_DEVELOPMENT_SUPPORT
		static bool debugProfile = true;
		
		static void APIENTRY DebugGLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
		{
			Logging::Type logType = Logging::Type::Other;
			Logging::Source logSource = Logging::Source::Other;
			Logging::Severity logSeverity = Logging::Severity::Info;

			switch(source)
			{
			case GL_DEBUG_SOURCE_API:
				logSource = Logging::Source::GraphicsApi;
				break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
				logSource = Logging::Source::WindowSystem;
				break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER:
				logSource = Logging::Source::ShaderCompiler;
				break;
			case GL_DEBUG_SOURCE_THIRD_PARTY:
				logSource = Logging::Source::ThirdParty;
				break;
			case GL_DEBUG_SOURCE_APPLICATION:
				logSource = Logging::Source::Application;
				break;
			default:
				logSource = Logging::Source::Other;
				break;
			}

			switch(type)
			{
			case GL_DEBUG_TYPE_ERROR:
				logType = Logging::Type::Error;
				break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				logType = Logging::Type::Deprecated;
				break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				logType = Logging::Type::UndefinedBehavior;
				break;
			case GL_DEBUG_TYPE_PORTABILITY:
				logType = Logging::Type::Protability;
				break;
			case GL_DEBUG_TYPE_PERFORMANCE:
				logType = Logging::Type::Performance;
				break;
			case GL_DEBUG_TYPE_MARKER:
				logType = Logging::Type::Marker;
				break;
			case GL_DEBUG_TYPE_PUSH_GROUP:
				logType = Logging::Type::PushGroup;
				break;
			case GL_DEBUG_TYPE_POP_GROUP:
				logType = Logging::Type::PopGroup;
				break;
			default:
				logType = Logging::Type::Other;
				break;
			}

			switch (severity)
			{
			case GL_DEBUG_SEVERITY_LOW:
				logSeverity = Logging::Severity::Low;
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				logSeverity = Logging::Severity::Medium;
				break;
			case GL_DEBUG_SEVERITY_HIGH:
				logSeverity = Logging::Severity::High;
				break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				logSeverity = Logging::Severity::Info;
				break;
			}

			StdExt::String strMessage( reinterpret_cast<const char8_t*>(message), length);

			Logging::log(logType, logSource, logSeverity, strMessage);
		}
#	else
		static bool debugProfile = false;

		static void APIENTRY DebugGLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
		{
		}
#	endif

	static OpenGL::Format MasterFormat()
	{
		OpenGL::Format fmt;
		fmt.versionMajor = 4;
		fmt.versionMinor = 2;
		fmt.versionProfile = OpenGL::Profile::COMPATIBILITY;
		fmt.debug = debugProfile;

		return fmt;
	}
	
	////////////////////////////////////////////////

	static thread_local GpuPipeline* currentPipeline = nullptr;

	GpuPipeline::GpuPipeline(GpuPipeline* shared)
	{
		flush = false;

		if (shared)
		{
			Concurrent::Condition initFinished;

			shared->enqueue([&]()
			{
				mRunContext = new OpenGL::Context(shared->mRunContext);
				mWaitContext = new OpenGL::Context(shared->mRunContext);
				initFinished.trigger();
			});

			initFinished.wait();
		}
		else
		{
			mRunContext = new OpenGL::Context(MasterFormat());
			
			mRunContext->makeCurrent();
			{
				mWaitContext = new OpenGL::Context(mRunContext);
			}
			mRunContext->doneCurrent();
		}
	}

	GpuPipeline::~GpuPipeline()
	{
		mTaskQueue.end();
		wait();

		delete mRunContext;
		delete mWaitContext;
	}

	void GpuPipeline::enqueue(std::function<void()>&& func)
	{
		mTaskQueue.push(std::forward<std::function<void()>>(func));
	}

	void GpuPipeline::setTarget(GPU::RenderTarget* target)
	{
		mRunContext->makeCurrent(target);
	}

	void GpuPipeline::swapBuffers()
	{
		mRunContext->swapBuffers();
	}

	void GpuPipeline::markForFlush()
	{
		// Enqueue setting the flag so we know the
		// logic that checks for the flag and does
		// the actual flush will not wait to run,
		// which would defeat the purpose.
		enqueue([this]()
		{
			flush = true;
		});
	}

	void GpuPipeline::run()
	{
		subtask(
			[this]()
			{
				mWaitContext->makeCurrent();

				OpenGL::Format fmt = MasterFormat();

				if (fmt.debug)
					initGLDebug(fmt, &DebugGLCallback, this);

				try
				{
					while ( true )
					{
						Fence* fence = nullptr;
						mFenceQueue.consume(fence);

						glClientWaitSync(fence->mApiFence, GL_SYNC_FLUSH_COMMANDS_BIT, std::numeric_limits<GLuint64>::max());
						glDeleteSync(fence->mApiFence);
						fence->mApiFence = 0;
						fence->done.trigger();
					}
				}
				catch ( object_destroyed )
				{
					mWaitContext->doneCurrent();
				}
			}
		);

		mRunContext->makeCurrent();

		OpenGL::Format fmt = MasterFormat();
		
		if ( fmt.debug )
			initGLDebug(fmt, &DebugGLCallback, this);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glClearColor(0.0, 0.0, 0.0, 0.0);

		try
		{
			while ( true )
			{
				std::function<void()> func;
				mTaskQueue.consume(func);

				func();
			}
		}
		catch ( object_destroyed )
		{
			mFenceQueue.end();
			mRunContext->doneCurrent();
		}
	}
#else
#	error Unsupported platform for GpuPipeline
#endif
}