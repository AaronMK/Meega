#include <Engine/Memory/VertexArrayObject.h>
#include <Engine/Tasking/Pipeline.h>
#include <Engine/Core/Utility.h>

using namespace StdExt;

namespace Engine
{
	VertexArrayObject::VertexArrayObject()
	{
		mHandle = 0;
	}

	VertexArrayObject::VertexArrayObject(VertexArrayObject&& other)
	{
		Concurrent::Condition done;

		Render::enqueue([this, &other, &done]()
		{
			mHandle = other.mHandle;
			other.mHandle = 0;

			done.trigger();
		});

		done.wait();
	}

	VertexArrayObject::~VertexArrayObject()
	{
		if (0 != mHandle)
		{
			Render::enqueue([=]()
			{
				glDeleteVertexArrays(1, &mHandle);
			});
		}
	}

	VertexArrayObject& VertexArrayObject::operator=(VertexArrayObject&& other)
	{

		Concurrent::Condition done;

		Render::enqueue([this, &other, &done]()
		{
			if (0 != mHandle)
				glDeleteVertexArrays(1, &mHandle);

			mHandle = other.mHandle;
			other.mHandle = 0;

			done.trigger();
		});

		done.wait();

		return *this;
	}

	void VertexArrayObject::bind(VertexArrayObject *vao)
	{
		if (0 == vao->mHandle)
			glGenVertexArrays(1, &vao->mHandle);

		glBindVertexArray(vao->mHandle);
	}

	void VertexArrayObject::unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArrayObject::enableAttribArray(int index)
	{
		glEnableVertexAttribArray(index);
	}

	void VertexArrayObject::attribPointerFloat(unsigned int index, int size, bool normalized, int stride, int byteOffset)
	{
		glVertexAttribPointer(index, size, GL_FLOAT, normalized, stride, (GLbyte*)(0) + byteOffset);
	}

	void VertexArrayObject::drawArrays(Mode mode, int first, int count)
	{
		glDrawArrays(enumVal(mode), first, count);
	}
}