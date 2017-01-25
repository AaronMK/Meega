#ifndef _ENGINE_VERTEX_ARRAY_OBJECT_H_
#define _ENGINE_VERTEX_ARRAY_OBJECT_H_

#include "../Core/Types.h"

#include "../Internal/Memory/VertexArrayObjectPlatform.h"

namespace Engine
{
	class ENGINE_EXPORT VertexArrayObject : public VertexArrayObjectPlatform
	{
	public:
		enum class Mode : Mode_t
		{
			Points                  = Points_v,
			Lines                   = Lines_v,
			LineLoop                = LineLoop_v,
			LineStrip               = LineStrip_v,
			LineStripAdjacency      = LineStripAdjacency_v,
			LinesAdjacency          = LinesAdjacency_v,
			TriangleStrip           = TriangleStrip_v,
			TriangleFan             = TriangleFan_v,
			Triangles               = Triangles_v,
			TriangleStripAdjacency  = TriangleStripAdjacency_v,
			TrianglesAdjacency      = TrianglesAdjacency_v,
			Patches                 = Patches_v
		};

		VertexArrayObject();
		VertexArrayObject(VertexArrayObject&& other);

		virtual ~VertexArrayObject();

		VertexArrayObject& operator=(VertexArrayObject&& other);

		static void bind(VertexArrayObject *vao);
		static void unbind();

		static void enableAttribArray(int index);

		static void attribPointerFloat(unsigned int index, int size, bool normalized, int stride, int byteOffset);

		static void drawArrays(Mode mode, int first, int count);
	};

	typedef VertexArrayObject VAO;
}

#endif // _ENGINE_VERTEX_ARRAY_OBJECT_H_