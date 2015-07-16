#ifndef _ENGINE_VERTEX_BUFFER_OBJECT_H_
#define _ENGINE_VERTEX_BUFFER_OBJECT_H_

#include <Engine/Internal/Memory/VertexBufferObjectPlatform.h>

namespace Engine
{
	class ENGINE_DYNAMIC_CLASS VertexBufferObject : public VertexBufferObjectPlatform
	{
	public:
		enum class Usage : Usage_t
		{
			StreamDraw                = UsageStreamDraw_v,
			StreamRead                = UsageStreamRead_v,
			StreamCopy                = UsageStreamCopy_v,
			StaticDraw                = UsageStaticDraw_v,
			StaticRead                = UsageStaticRead_v,
			StaticCopy                = UsageStaticCopy_v,
			DynamicDraw               = UsageDynamicDraw_v,
			DynamicRead               = UsageDynamicRead_v,
			DynamicCopy               = UsageDynamicCopy_v
		};

		enum class Target : Target_t
		{
			Array                 = TargetArrayBuffer_v,
			AtomicCounter         = TargetAtomicCounterBuffer_v,
			CopyRead              = TargetCopyReadBuffer_v,
			CopyWrite             = TargetCopyWriteBuffer_v,
			DispatchIndirect      = TargetDispatchIndirectBuffer_v,
			DrawIndirect          = TargetDrawIndirectBuffer_v,
			ElementArray          = TargetElementArrayBuffer_v,
			PixelPack             = TargetPixelPackBuffer_v,
			PixelUnpack           = TargetPixelUnpackBuffer_v,
			Query                 = TargetQueryBuffer_v,
			ShaderStorage         = TargetShaderStorageBuffer_v,
			Texture               = TargetTextureBuffer_v,
			TransformFeedback     = TargetTransformFeedbackBuffer_v,
			Uniform               = TargetUniformBuffer_v
		};

		VertexBufferObject();
		VertexBufferObject(VertexBufferObject&& other);

		virtual ~VertexBufferObject();

		VertexBufferObject& operator=(VertexBufferObject&& other);

		static void bind(VertexBufferObject *vbo, Target target);
		static void unbind(Target target);

		static void BufferData(Target target, unsigned int size,
	                           void* data, Usage usage);
	};

	typedef VertexBufferObject VBO;
}

#endif // _ENGINE_VERTEX_BUFFER_OBJECT_H_