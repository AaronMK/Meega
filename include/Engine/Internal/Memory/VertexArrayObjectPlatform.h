#ifndef _ENGINE_VERTEX_ARRAY_OBJECT_PLATFORM_H_
#define _ENGINE_VERTEX_ARRAY_OBJECT_PLATFORM_H_

#include "../../Config.h"

#ifdef ENGINE_API_OPEN_GL

#include <GPU/OpenGL/Common.h>

namespace Engine
{
	class ENGINE_EXPORT VertexArrayObjectPlatform
	{
	protected:
		typedef GLenum Mode_t;
		static const Mode_t Points_v                   = GL_POINTS;
		static const Mode_t Lines_v                    = GL_LINES;
		static const Mode_t LineLoop_v                 = GL_LINE_LOOP;
		static const Mode_t LineStrip_v                = GL_LINE_STRIP; 
		static const Mode_t LineStripAdjacency_v       = GL_LINE_STRIP_ADJACENCY;
		static const Mode_t LinesAdjacency_v           = GL_LINES_ADJACENCY;
		static const Mode_t TriangleStrip_v            = GL_TRIANGLE_STRIP;
		static const Mode_t TriangleFan_v              = GL_TRIANGLE_FAN;
		static const Mode_t Triangles_v                = GL_TRIANGLES;
		static const Mode_t TriangleStripAdjacency_v   = GL_TRIANGLES_ADJACENCY;
		static const Mode_t TrianglesAdjacency_v       = GL_TRIANGLES_ADJACENCY;
		static const Mode_t Patches_v                  = GL_PATCHES;

		GLuint mHandle;
	};
}

#endif

#endif // _ENGINE_VERTEX_ARRAY_OBJECT_PLATFORM_H_