#include "App.h"

App::App()
{
}

void App::start()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	m_window.createWindow();
	if (m_window.getWindow() == NULL)
	{
		std::cout << "FAILED TO CREATE WINDOW\n";
		glfwTerminate();
		exit(-1);
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "FAILED TO INIT GLAD\n";
		exit(-1);
	}

	glEnable(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shaderText.CompileShader("src/render/shaders/Text.vert", "src/render/shaders/Text.frag");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_window.getWidth()), 0.0f, static_cast<float>(m_window.getHeight()));
	shaderText.use();
	glUniformMatrix4fv(glGetUniformLocation(shaderText.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	textClass.init("res/font/Orange Kid.otf", 250);

	shader.CompileShader("src/render/shaders/shader.vert", "src/render/shaders/shader.frag");
	
	ui.init();

	ball.init();

	player1.init();
	player1.setPosition(glm::vec3(-1.5,0.0,0.0));

	player2.init();
	player2.setPosition(glm::vec3(1.5, 0.0, 0.0));

	m_aspect = (float)m_window.getWidth() / (float)m_window.getHeight();
	m_projection = glm::ortho(-m_aspect, m_aspect, -1.0f, 1.0f, -1.0f, 1.0f);
}

void App::run()
{
	while (gameEnd == false)
	{
		float currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		input(m_window.getWindow());

		//update
		//collision
		if (m_count == true)
		{
			m_timer += m_deltaTime;
			if (m_timer > 0.2)
			{
				m_count = false;
				m_timer = 0;
			}
		}
		if (m_timer == 0)
		{
			chectCollision(&ball, &player1);
			chectCollision(&ball, &player2);
		}
		ball.windowCollision();

		player1.windowCollision();
		player2.windowCollision();

		//ball
		ball.OnUpdate(m_deltaTime);

		//render

		shader.use();
		shader.setMat4("projection", m_projection);

		ui.middleLine(shader);

		player1.render(shader);
		player2.render(shader);

		ball.render(shader);

		char Player1Points[32];
		itoa(player1.getScore(), Player1Points, 10);
		textClass.RenderText(shaderText, Player1Points, m_window.getWidth() / 4, (m_window.getHeight() / 5) * 4, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

		char Player2Points[32];
		itoa(player2.getScore(), Player2Points, 10);
		textClass.RenderText(shaderText, Player2Points, (m_window.getWidth() / 4) * 3, (m_window.getHeight() / 5) * 4, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

		m_window.OnUpdate();
		GameLogic();
	}
}

void App::input(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		gameEnd = true;
		glfwSetWindowShouldClose(window, true);
	}

	//PLAYER1
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		player1.processInput(UP, m_deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		player1.processInput(DOWN, m_deltaTime);
	}

	//PLAYER2
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		player2.processInput(UP, m_deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		player2.processInput(DOWN, m_deltaTime);
	}
}

void App::chectCollision(Ball* ball, Player* player)
{
	bool collisionX = ball->getPosition().x + ball->m_height/2 >= player->getPosition().x - player->m_width /2 &&
		              player->getPosition().x + player->m_width/2 >= ball->getPosition().x - ball->m_height /2;
	
	bool collisionY = ball->getPosition().y + ball->m_height/2 >= player->getPosition().y - player->m_height /2 &&
		              player->getPosition().y + player->m_height/2 >= ball->getPosition().y - ball->m_height /2;

	if (collisionX && collisionY)
	{
		m_count = true;
		ball->swapVelX();
	}
}

void App::close()
{
	m_window.TerminateWindow();
	glfwTerminate();
}

void App::GameLogic()
{
	if (ball.getLeftCol())
	{
		player2.addScore();
		ball.setLeftCol(false);
	}
	if (ball.getRightCol())
	{
		player1.addScore();
		ball.setRightCol(false);
	}
	if (player1.getScore() == 15)
	{
		gameEnd = true;
		glfwSetWindowShouldClose(m_window.getWindow(), true);
	}
	if (player2.getScore() == 15)
	{
		gameEnd = true;
		glfwSetWindowShouldClose(m_window.getWindow(), true);
	}
}
