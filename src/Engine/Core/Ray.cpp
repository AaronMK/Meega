#include <Engine/Core/Ray.h>

#include <Engine/Core/Math3d.h>

namespace Engine
{
	Ray3::Ray3(const Ray4 &other)
	{
		org = point(other.org);
		dir = vector(other.dir);
	}

	Ray3::Ray3(const vec3 &origin, const vec3 &direction)
		: org(origin), dir(direction)
	{
	}

	Ray3::Ray3(const vec4 &origin, const vec4 &direction)
	{
		
		org = point(origin);
		dir = vector(direction);
	}

	/////////////////////////////////////////////////////////

	Ray4::Ray4(const Ray3 &ray_3)
		: Ray4(ray_3.org, ray_3.dir)
	{
	}

	Ray4::Ray4(const vec3 &origin, const vec3 &direction)
	{
		org = vec4(
			origin[0], 
			origin[1], 
			origin[2],
			1.0f
		);

		dir = (
			direction[0],
			direction[1],
			direction[2],
			0.0f
		);
	}

	Ray4::Ray4(const vec4 &origin, const vec4 &direction)
		: org(origin), dir(direction)
	{
	}
}