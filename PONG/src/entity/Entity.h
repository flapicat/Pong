#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "render/Shader.h"
#include "render/VAO.h"
#include "render/VBO.h"
#include "render/EBO.h"

class Entity
{
public:
	Entity();

	void setPosition(glm::vec3 pos);
	glm::vec3 getPosition();

	virtual void OnUpdate() = 0;

	virtual void render(Shader& shader) = 0;
protected:
	render::VAO vao;
	render::VBO vbo;
	render::EBO ebo;
	glm::vec3 m_position;
};

