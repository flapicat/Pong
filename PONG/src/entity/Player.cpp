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
	ebo.attachIndices(m_indices, sizeof(m_indices));

	vao.linkVBO(vbo, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	vao.unbind();
}

void Player::processInput(MOVES action, float deltaTme)
{
	if (action == UP)
	{
		m_position.y += 1 * m_speed * deltaTme;
	}
	if (action == DOWN)
	{
		m_position.y += -1 * m_speed * deltaTme;
	}
	if (action == LEFT)
	{
		m_position.x += -1 * m_speed * deltaTme;
	}
	if (action == RIGHT)
	{
		m_position.x += 1 * m_speed * deltaTme;
	}
}

void Player::windowCollision()
{
	if (m_position.y >= 1 - m_height /2)
	{
		m_position.y = 1 - m_height / 2;
	}
	if (m_position.y <= -1 + m_height / 2)
	{
		m_position.y = -1 + m_height / 2;
	}
}

int Player::getScore()
{
	return m_score;
}

void Player::addScore()
{
	m_score++;
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
