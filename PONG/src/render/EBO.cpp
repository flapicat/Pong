#include "EBO.h"


namespace render
{
	EBO::EBO()
	{
	}

	void EBO::attachIndices(unsigned int* indices, GLsizeiptr size)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	void EBO::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void EBO::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void EBO::Delete()
	{
		glDeleteBuffers(1, &ID);
	}
}