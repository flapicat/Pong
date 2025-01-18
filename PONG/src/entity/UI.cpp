#include "UI.h"

UI::UI()
{
}

void UI::init()
{
	m_position = glm::vec3(0.0f, 1.0f, 0.0f);
	vao.createVAO();
	vao.bind();

	vbo.linkVBO(vertices, sizeof(vertices));
	ebo.attachIndices(indices, sizeof(indices));

	vao.linkVBO(vbo, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	vao.unbind();
}

void UI::middleLine(Shader& shader)
{
	m_position.y = 1.0 - height/3;
	for (int i = 0; i < 7; i++)
	{
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, m_position);
		shader.setMat4("transform", transform);

		vao.bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		vao.unbind();
		m_position.y -= height ;
	}
}
