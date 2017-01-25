#ifndef _ENGINE_VERTEX_BUFFER_OBJECT_H_
#define _ENGINE_VERTEX_BUFFER_OBJECT_H_

#include  "../Internal/Memory/VertexBufferObjectPlatform.h"

namespace Engine
{
	class ENGINE_EXPORT VertexBufferObject : public VertexBufferObjectPlatform
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

		/**
		 * @brief
		 *  Targets to which a VBO can be bound
		 */
		enum class Target : Target_t
		{
			/**
			 * @brief
			 *  Vertex attributes
			 */
			Array                 = TargetArrayBuffer_v,

			/**
			 * @brief
			 *  Atomic counter storage
			 */
			AtomicCounter         = TargetAtomicCounterBuffer_v,

			/**
			 * @brief
			 *  Buffer copy source
			 */
			CopyRead              = TargetCopyReadBuffer_v,

			/**
			 * @brief
			 *  Buffer copy destination
			 */
			CopyWrite             = TargetCopyWriteBuffer_v,

			/**
			 * @brief
			 *  Indirect compute dispatch commands
			 */
			DispatchIndirect      = TargetDispatchIndirectBuffer_v,

			/**
			 * @brief
			 *  Indirect command arguments
			 */
			DrawIndirect          = TargetDrawIndirectBuffer_v,

			/**
			 * @brief
			 *  Vertex array indices
			 */
			ElementArray          = TargetElementArrayBuffer_v,

			/**
			 * @brief
			 *  Pixel read target
			 */
			PixelPack             = TargetPixelPackBuffer_v,

			/**
			 * @brief
			 *  Texture data source
			 */
			PixelUnpack           = TargetPixelUnpackBuffer_v,

			/**
			 * @brief
			 *  Query result buffer
			 */
			Query                 = TargetQueryBuffer_v,

			/**
			 * @brief
			 *  Read-write storage for shaders
			 */
			ShaderStorage         = TargetShaderStorageBuffer_v,

			/**
			 * @brief
			 *  Texture data buffer
			 */
			Texture               = TargetTextureBuffer_v,

			/**
			 * @brief
			 *  Transform feedback buffer
			 */
			TransformFeedback     = TargetTransformFeedbackBuffer_v,

			/**
			 * @brief
			 *  Uniform block storage
			 */
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