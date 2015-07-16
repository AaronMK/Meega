#include <Engine/Core/Ray.h>

namespace Engine
{
	Ray3::Ray3()
	{
	}

	Ray3::Ray3(const Ray3 &other)
	: org(other.org), dir(other.dir)
	{
	}

	Ray3::Ray3(const Ray4 &other)
	: org(other.org), dir(other.dir)
	{
	}

	Ray3::Ray3(const vec3 &origin, const vec3 &direction)
	: org(origin), dir(direction)
	{
	}

	Ray3::Ray3(const vec4 &origin, const vec4 &direction)
	: org(origin), dir(direction)
	{
	}

	/////////////////////////////////////////////////////////
	
	Ray4::Ray4()
	{
	}

	Ray4::Ray4(const Ray3 &other)
	: org(other.org), dir(other.dir)
	{
	}

	Ray4::Ray4(const Ray4 &other)
	: org(other.org), dir(other.dir)
	{
	}

	Ray4::Ray4(const vec3 &origin, const vec3 &direction)
	: org(origin), dir(direction)
	{
	}

	Ray4::Ray4(const vec4 &origin, const vec4 &direction)
	: org(origin), dir(direction)
	{
	}
}