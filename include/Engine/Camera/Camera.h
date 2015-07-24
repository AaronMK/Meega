#ifndef _ENGINE_CAMERA_H_
#define _ENGINE_CAMERA_H_

#include <Engine/Core/Transform.h>

namespace Engine
{
	/**
	 * Camera interface.  Cameras do not typically interact with OpenGL directly, just provide matricies that
	 * define projection and modelview transformations for use as the engine sees fit.  This could be for ray
	 * generation, passing as parameters to a shader or pre-OpenGL 3.2 calls.
	 */
	class ENGINE_DYNAMIC_CLASS Camera : public Align16
	{
	public:
		Camera(const Camera&) = default;

		Camera();
		virtual ~Camera();

		enum class CullResult
		{
			Partial,
			Outside,
			Inside
		};

		const mat4x4& projection() const;
		const mat4x4& modelview() const;

		void setLookAt(const vec3 &Eye, const vec3 &Center, const vec3 &Up);
		void setPerspective(float fovyDegrees, float pxWidth, float pxHeight, float zNear, float zFar);
		void setOrthographic(float left, float right, float bottom, float top, float zNear, float zFar);

	protected:
		Transform transProjection;
		Transform transModelview;
		Transform transRasterToCamera;
	};
}

#endif // _ENGINE_CAMERA_H_