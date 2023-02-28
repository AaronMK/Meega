#include <Engine/Memory/VertexBufferObject.h>

#include <Engine/Tasking/Pipeline.h>
#include <Engine/Core/Utility.h>

#include <cassert>

namespace Engine
{
	VertexBufferObject::VertexBufferObject()
	{
		mHandle = 0;
	}

	VertexBufferObject::VertexBufferObject(VertexBufferObject&& other)
	{
		StdExt::Concurrent::Condition done;

		Render::enqueue([this, &other, &done]()
		{
			mHandle = other.mHandle;
			other.mHandle = 0;

			done.trigger();
		});

		done.wait();
	}

	VertexBufferObject::~VertexBufferObject()
	{
		if (0 != mHandle)
		{
			Load::enqueue([=]()
			{
				glDeleteBuffers(1, &mHandle);
			});
		}
	}

	VertexBufferObject& VertexBufferObject::operator=(VertexBufferObject&& other)
	{
		StdExt::Concurrent::Condition done;

		Render::enqueue([this, &other, &done]()
		{
			if (0 != mHandle)
				glDeleteBuffers(1, &mHandle);

			mHandle = other.mHandle;
			other.mHandle = 0;

			done.trigger();
		});

		done.wait();

		return *this;
	}

	void VertexBufferObject::bind(VertexBufferObject *vbo, Target target)
	{
		if (0 == vbo->mHandle)
			glGenBuffers(1, &vbo->mHandle);

		glBindBuffer(enumVal(target), vbo->mHandle);
	}

	void VertexBufferObject::unbind(Target target)
	{
		glBindBuffer(enumVal(target), 0);
	}

	void VertexBufferObject::BufferData(VBO::Target target, unsigned int size, void* data, VBO::Usage usage)
	{
		glBufferData(enumVal(target), size, data, enumVal(usage));
	}
}