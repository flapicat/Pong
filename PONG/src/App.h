#pragma once

#include <memory>
#include <chrono>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Window.h"
#include "render/Shader.h"

#include "entity/Ball.h"
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
	void chectCollision(Ball* ball, Player* player);
private:
	void GameLogic();
	bool m_count = false;
	float m_timer = 0;
	float m_aspect;
	glm::mat4 m_projection;
	float m_deltaTime = 0, m_lastFrame = 0;

	Shader shader;
	Window m_window;

	UI ui;

	Player player1;
	Player player2;
	Ball ball;
};

