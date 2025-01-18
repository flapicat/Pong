#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "render/Shader.h"
#include "render/VAO.h"
#include "render/VBO.h"
#include "render/EBO.h"

class UI
{
public:
    UI();
    void init();

    void middleLine(Shader& shader);
private:
    float height = 0.3;

    float vertices[12] = {
       0.01f,  height/4 , 0.0f, // Top-right
      -0.01f,  height/4 , 0.0f, // Top-left
      -0.01f, -height/4 , 0.0f, // Bottom-left
       0.01f, -height/4 , 0.0f  // Bottom-right
    };
    unsigned int indices[6] = {
        0, 1, 2, // First triangle
        0, 2, 3  // Second triangle
    };

    render::VAO vao;
    render::VBO vbo;
    render::EBO ebo;
    glm::vec3 m_position;
};

