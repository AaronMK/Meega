#ifndef _ENGINE_CAMERA_H_
#define _ENGINE_CAMERA_H_

#include "../Core/Transform.h"
#include "../Core/Units.h"

namespace Engine
{
	/**
	 * @brief
	 *  Camera interface.
	 *
	 * @details
	 *  Cameras do not typically interact with the graphics API directly, just provide matricies that
	 *  define projection and modelview transformations for use as the engine sees fit.  This could be for ray
	 *  generation, passing as parameters to a shader or pre-OpenGL 3.2 calls.
	 */
	class ENGINE_EXPORT Camera
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

		const Transform& projection() const;
		const Transform& world() const;

		void setLookAt(const vec3 &Eye, const vec3 &Center, const vec3 &Up);
		void setPerspective(const Degrees &fovy, float pxWidth, float pxHeight, float zNear, float zFar);
		void setOrthographic(float left, float right, float bottom, float top, float zNear, float zFar);

	protected:
		Transform transProjection;
		Transform transWorld;
		Transform transRasterToCamera;
	};
}

#endif // _ENGINE_CAMERA_H_