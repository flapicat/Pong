#pragma once

#include <map>
#include <string>
#include <memory>
#include <chrono>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Window.h"
#include "render/Shader.h"

#include "entity/Ball.h"
#include "entity/Player.h"
#include "entity/UI.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "TextClass.h"

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
	bool gameEnd = false;
	void GameLogic();
	bool m_count = false;
	float m_timer = 0;
	float m_aspect;
	glm::mat4 m_projection;
	float m_deltaTime = 0, m_lastFrame = 0;

	TextClass textClass;
	Shader shader;
	Shader shaderText;

	Window m_window;

	UI ui;

	Player player1;
	Player player2;
	Ball ball;
};