#include "Player.h"

Player::Player()
{
}

void Player::init()
{
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	vao.createVAO();
	vao.bind();

	vbo.linkVBO(vertices, sizeof(vertices));
	ebo.attachIndices(indices, sizeof(indices));

	vao.linkVBO(vbo, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	vao.unbind();
}

void Player::processInput(MOVES action, float deltaTme)
{
	if (action == UP)
	{
		m_position.y += 1 * speed * deltaTme;
	}
	if (action == DOWN)
	{
		m_position.y += -1 * speed * deltaTme;
	}
}

void Player::OnUpdate()
{
	windowCollision();
	//std::cout << "POSITION: " << m_position.x << ", " << m_position.y << ", " << m_position.z << "\n ";
}

void Player::windowCollision()
{
	if (m_position.y >= 1 - height /2)
	{
		m_position.y = 1 - height / 2;
	}
	if (m_position.y <= -1 + height / 2)
	{
		m_position.y = -1 + height / 2;
	}
}

void Player::render(Shader& shader)
{
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, m_position);
	shader.setMat4("transform", transform);

	vao.bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	vao.unbind();
}
