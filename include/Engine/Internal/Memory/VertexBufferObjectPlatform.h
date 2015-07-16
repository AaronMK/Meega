#ifndef _ENGINE_VERTEX_BUFFER_OBJECT_PLATFORM_H_
#define _ENGINE_VERTEX_BUFFER_OBJECT_PLATFORM_H_

#include <Engine/Config.h>

#ifdef ENGINE_API_OPEN_GL

#include <GPU/OpenGL/Common.h>

namespace Engine
{
	class ENGINE_DYNAMIC_CLASS VertexBufferObjectPlatform
	{
	public:

		typedef GLenum Target_t;
		static const GLenum TargetArrayBuffer_v              = GL_ARRAY_BUFFER;
		static const GLenum TargetAtomicCounterBuffer_v      = GL_ATOMIC_COUNTER_BUFFER;
		static const GLenum TargetCopyReadBuffer_v           = GL_COPY_READ_BUFFER;
		static const GLenum TargetCopyWriteBuffer_v          = GL_COPY_WRITE_BUFFER;
		static const GLenum TargetDispatchIndirectBuffer_v   = GL_DISPATCH_INDIRECT_BUFFER;
		static const GLenum TargetDrawIndirectBuffer_v       = GL_DRAW_INDIRECT_BUFFER;
		static const GLenum TargetElementArrayBuffer_v       = GL_ELEMENT_ARRAY_BUFFER;
		static const GLenum TargetPixelPackBuffer_v          = GL_PIXEL_PACK_BUFFER;
		static const GLenum TargetPixelUnpackBuffer_v        = GL_PIXEL_UNPACK_BUFFER;
		static const GLenum TargetQueryBuffer_v              = GL_QUERY_BUFFER;
		static const GLenum TargetShaderStorageBuffer_v      = GL_SHADER_STORAGE_BUFFER;
		static const GLenum TargetTextureBuffer_v            = GL_TEXTURE_BUFFER;
		static const GLenum TargetTransformFeedbackBuffer_v  = GL_TRANSFORM_FEEDBACK_BUFFER;
		static const GLenum TargetUniformBuffer_v            = GL_UNIFORM_BUFFER;

		typedef GLenum Usage_t;
		static const GLenum UsageStreamDraw_v                = GL_STREAM_DRAW;
		static const GLenum UsageStreamRead_v                = GL_STREAM_READ;
		static const GLenum UsageStreamCopy_v                = GL_STREAM_COPY;
		static const GLenum UsageStaticDraw_v                = GL_STATIC_DRAW;
		static const GLenum UsageStaticRead_v                = GL_STATIC_READ;
		static const GLenum UsageStaticCopy_v                = GL_STATIC_COPY;
		static const GLenum UsageDynamicDraw_v               = GL_DYNAMIC_DRAW;
		static const GLenum UsageDynamicRead_v               = GL_DYNAMIC_READ;
		static const GLenum UsageDynamicCopy_v               = GL_DYNAMIC_COPY;

		GLuint mHandle;

	protected:
		GLenum mBoundTarget;
	};
}

#endif

#endif // _ENGINE_VERTEX_BUFFER_OBJECT_PLATFORM_H_