#pragma once
#include "VBO.h"

namespace render
{
	class VAO
	{
	public:
		VAO();
		void createVAO();

		void linkVBO(VBO& VBO, GLuint layout, GLint size, GLenum type, GLboolean normalized, GLsizei strind, const void* pointer);
		void bind();
		void unbind();
		void Delete();
	private:
		unsigned int ID;
	};
}