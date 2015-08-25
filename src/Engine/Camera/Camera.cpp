#include <Engine/Camera/Camera.h>
#include <Engine/Core/Transform.h>
#include <Engine/Core/math3d.h>

#include <limits>

namespace Engine
{	
	Camera::Camera()
	{
	}

	Camera::~Camera()
	{
	}

	const Transform& Camera::projection() const
	{
		return transProjection;
	}

	const Transform& Camera::world() const
	{
		return transWorld;
	}

	void Camera::setLookAt(const vec3 &Eye, const vec3 &Center, const vec3 &Up)
	{
		vec3 Forward = Center - Eye;
		vec3 normUp = Up;
		vec3 Right;
		
		orthonormalBasis(&Forward, &normUp, &Right);

		mat4x4 rot(    Right[0],    Right[1],    Right[2],  0.0f,
		              normUp[0],   normUp[1],   normUp[2],  0.0f,
		            -Forward[0], -Forward[1], -Forward[2],  0.0f,
		                   0.0f,        0.0f,        0.0f,  1.0f);

		mat4x4 trans(1.0f, 0.0f, 0.0f, -Eye[0],
		             0.0f, 1.0f, 0.0f, -Eye[1],
		             0.0f, 0.0f, 1.0f, -Eye[2],
		             0.0f, 0.0f, 0.0f,    1.0f);

		transWorld = rot * trans;
	}

	void Camera::setPerspective(float fovyDegrees, float pxWidth, float pxHeight, float zNear, float zFar)
	{	
		float aspect = pxWidth/pxHeight;
		float coTan = 1.0f/tan( toRadians(fovyDegrees) );

		transProjection = mat4x4( coTan/aspect, 0.0f,  0.0f,                          0.0f,
		                          0.0f,         coTan, 0.0f,                          0.0f,
		                          0.0f,         0.0f,  (zFar + zNear)/(zNear - zFar), (2.0f*zFar*zNear)/(zNear - zFar),
		                          0.0f,         0.0f,  -1.0f,                         0.0f                            );

		transRasterToCamera = Transform::RasterToScreen(pxWidth, pxHeight) * transProjection.inverse();
	}

	void Camera::setOrthographic(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		float tX = (right + left)/(right - left);
		float tY = (top + bottom)/(top - bottom);
		float tZ = (zFar + zNear)/(zFar - zNear);

		transProjection = mat4x4( 2.0f/(right - left), 0.0f,                0.0f,                 -tX,
		                          0.0f,                2.0f/(top - bottom), 0.0f,                 -tY,
		                          0.0f,                0.0f,                -2.0f/(zFar - zNear), -tZ,
		                          0.0f,                0.0f,                0.0f,                 1.0f);

		transRasterToCamera = Transform::RasterToScreen(right - left, top - bottom) * transProjection.inverse();
	}
}