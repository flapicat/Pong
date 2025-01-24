#include "Ball.h"

Ball::Ball()
{
}

void Ball::init()
{
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	vao.createVAO();
	vao.bind();

	vbo.linkVBO(vertices, sizeof(vertices));
	ebo.attachIndices(indices, sizeof(indices));

	vao.linkVBO(vbo, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	vao.unbind();
}

void Ball::OnUpdate(float deltaTime)
{
	m_position.x += m_velocityX * m_speed * deltaTime;
	m_position.y += m_velocityY * m_speed * deltaTime;
}

float Ball::getVelX()
{
	return m_velocityX;
}

float Ball::getVelY()
{
	return m_velocityY;
}

void Ball::setVelX(float x)
{
	m_velocityX = x;
}

void Ball::setVelY(float y)
{
	m_velocityY = y;
}

void Ball::swapVelX()
{
	m_velocityX *= -1;
}

void Ball::swapVelY()
{
	m_velocityY *= -1;
}

void Ball::setLeftCol(bool x)
{
	m_leftCOL = x;
}

bool Ball::getLeftCol()
{
	return m_leftCOL;
}

void Ball::setRightCol(bool x)
{
	m_rightCOL = x;
}

bool Ball::getRightCol()
{
	return m_rightCOL;
}

void Ball::windowCollision()
{
	if (m_position.y >= 1 - m_height / 2) //top
	{
		m_velocityY *= -1;
	}
	if (m_position.y <= -1 + m_height / 2) //bot
	{
		m_velocityY *= -1;
	}
	
	if (m_position.x >= 1.75) //left
	{
		m_velocityX *= -1;
		m_leftCOL = true;
		m_position = glm::vec3(0.0f,0.0f,0.0f);
	}
	
	if (m_position.x <= -1.75) //right
	{
		m_velocityX *= -1;
		m_rightCOL = true;
		m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

float Ball::getHeight()
{
	return m_height;
}

void Ball::render(Shader& shader)
{
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, m_position);
	shader.setMat4("transform", transform);

	vao.bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	vao.unbind();
}
