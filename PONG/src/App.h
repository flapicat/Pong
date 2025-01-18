#pragma once

#include <memory>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Window.h"
#include "render/Shader.h"

#include "entity/Player.h"
#include "entity/UI.h"

class App
{
public:
	App();

	void start();
	void run();
	void close();
	void input(GLFWwindow* window);
	void chectCollision();
private:
	float aspect;
	glm::mat4 projection;
	float m_deltaTime, m_lastFrame;

	Shader shader;
	Window m_window;

	UI ui;

	Player player1;
	Player player2;
};

