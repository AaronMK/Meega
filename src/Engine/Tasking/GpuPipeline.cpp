#include "../private_include/Tasking/GpuPipeline.h"

#include <Concurrent/Scheduler.h>
#include <Concurrent/ThreadLocalPtr.h>

#include "../private_include/Debug/DebugGL.h"

#include <limits>
#include <sstream>

#include <Engine/DevSupport/Logging.h>

namespace Engine
{
#ifdef ENGINE_API_OPEN_GL
#	ifdef ENGINE_DEVEOPMENT_SUPPORT
		static bool debugProfile = true;
		
		static void APIENTRY DebugGLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
		{
			LogType logType;
			LogSource logSource;
			LogSeverity logSeverity;

			switch(source)
			{
			case GL_DEBUG_SOURCE_API:
				logSource = LogSource::GraphicsApi;
				break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
				logSource = LogSource::WindowSystem;
				break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER:
				logSource = LogSource::ShaderCompiler;
				break;
			case GL_DEBUG_SOURCE_THIRD_PARTY:
				logSource = LogSource::ThirdParty;
				break;
			case GL_DEBUG_SOURCE_APPLICATION:
				logSource = LogSource::Application;
				break;
			default:
				logSource = LogSource::Other;
				break;
			}

			switch(type)
			{
			case GL_DEBUG_TYPE_ERROR:
				logType = LogType::Error;
				break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				logType = LogType::Deprecated;
				break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				logType = LogType::UndefinedBehavior;
				break;
			case GL_DEBUG_TYPE_PORTABILITY:
				logType = LogType::Protability;
				break;
			case GL_DEBUG_TYPE_PERFORMANCE:
				logType = LogType::Performance;
				break;
			case GL_DEBUG_TYPE_MARKER:
				logType = LogType::Marker;
				break;
			case GL_DEBUG_TYPE_PUSH_GROUP:
				logType = LogType::PushGroup;
				break;
			case GL_DEBUG_TYPE_POP_GROUP:
				logType = LogType::PopGroup;
				break;
			default:
				logType = LogType::Other;
				break;
			}

			switch (severity)
			{
			case GL_DEBUG_SEVERITY_LOW:
				logSeverity = LogSeverity::Low;
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				logSeverity = LogSeverity::Medium;
				break;
			case GL_DEBUG_SEVERITY_HIGH:
				logSeverity = LogSeverity::High;
				break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				logSeverity = LogSeverity::Info;
				break;
			}

			std::string strMessage(message, length);

			int breakPt = 1;
		}
#	else
		static bool debugProfile = false;

		static void APIENTRY DebugGLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
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

	static Concurrent::ThreadLocalPtr<GpuPipeline> currentPipeline;

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

		mRunTask.setFunction(std::bind(&GpuPipeline::runThread, this));
		Concurrent::Scheduler::runAsThread(&mRunTask);

		mWaitTask.setFunction(std::bind(&GpuPipeline::waitThread, this));
		Concurrent::Scheduler::runAsThread(&mWaitTask);
	}

	GpuPipeline::~GpuPipeline()
	{
		mTaskQueue.end();
		mRunTask.wait();

		mFenceQueue.end();
		mWaitTask.wait();

		delete mRunContext;
		delete mWaitContext;
	}

	void GpuPipeline::enqueue(const std::function<void()> &func)
	{
		if (Concurrent::Task::current() == &mRunTask)
			func();
		else
			mTaskQueue.push(std::function<void()>(func));
	}

	void GpuPipeline::enqueue(std::function<void()>&& func)
	{
		if (Concurrent::Task::current() == &mRunTask)
			func();
		else
			mTaskQueue.push(std::move(func));
	}

	void GpuPipeline::setTarget(GPU::RenderTarget* target)
	{
		assert(Concurrent::Task::current() == &mRunTask);
		mRunContext->makeCurrent(target);
	}

	void GpuPipeline::swapBuffers()
	{
		assert(Concurrent::Task::current() == &mRunTask);
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

	void GpuPipeline::waitThread()
	{
		currentPipeline.set(this);

		mWaitContext->makeCurrent();

		OpenGL::Format fmt = MasterFormat();
		
		if (fmt.debug)
		{
			initGLDebug(fmt, &DebugGLCallback, this);
		}

		Fence* fence = nullptr;
		while (mFenceQueue.consume(fence))
		{
			glClientWaitSync(fence->mApiFence, GL_SYNC_FLUSH_COMMANDS_BIT, std::numeric_limits<GLuint64>::max());
			glDeleteSync(fence->mApiFence);
			fence->mApiFence = 0;
			fence->done.trigger();
		}

		mWaitContext->doneCurrent();

		currentPipeline.set(nullptr);
	}

	void GpuPipeline::runThread()
	{
		currentPipeline.set(this);

		mRunContext->makeCurrent();

		OpenGL::Format fmt = MasterFormat();
		
		if (fmt.debug)
			initGLDebug(fmt, &DebugGLCallback, this);

		std::function<void()> func;
		while (mTaskQueue.consume(func))
		{
			func();

			// If we are expecting more commands, hold off doing the
			// actual flush as they might fill the buffer.
			if (flush && mTaskQueue.isEmpty())
			{
				glFlush();
				flush = false;
			}
		}

		mRunContext->doneCurrent();

		currentPipeline.set(nullptr);
	}

	GpuPipeline* GpuPipeline::current()
	{
		return currentPipeline.get();
	}
#else
#	error Unsupported platform for GpuPipeline
#endif
}