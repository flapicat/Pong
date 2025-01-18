#include "VAO.h"

namespace render
{
	VAO::VAO()
	{
	}

	void VAO::createVAO()
	{
		glGenVertexArrays(1, &ID);
	}

	void VAO::linkVBO(VBO& VBO, GLuint layout, GLint size, GLenum type, GLboolean normalized, GLsizei strind, const void* pointer)
	{
		VBO.bind();

		glVertexAttribPointer(layout, size, type, normalized, strind, pointer);
		glEnableVertexAttribArray(layout);

		VBO.unbind();
	}

	void VAO::bind()
	{
		glBindVertexArray(ID);
	}

	void VAO::unbind()
	{
		glBindVertexArray(0);
	}

	void VAO::Delete()
	{
		glDeleteBuffers(1, &ID);
	}
}