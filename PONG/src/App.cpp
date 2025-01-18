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
	while (!glfwWindowShouldClose(m_window.getWindow()))
	{
		float currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		input(m_window.getWindow());
		
		//update
		if (m_count == true)
		{
			m_timer += m_deltaTime;
			if (m_timer > 0.5)
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
		player1.OnUpdate();
		player2.OnUpdate();

		//ball
		ball.OnUpdate(m_deltaTime);

		//render
		shader.use();
		shader.setMat4("projection", m_projection);

		ui.middleLine(shader);

		player1.render(shader);
		player2.render(shader);

		ball.render(shader);

		m_window.OnUpdate();

		GameLogic();

		//std::cout << "PLAYER1 SCORE: " << player1.getScore() << "		";
		//std::cout << "PLAYER2 SCORE: " << player2.getScore() << "\n";
	}
}

void App::input(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
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
		std::cout << "PLAYER 1 WIN\n";
		std::cout << "P1 score: " << player1.getScore() << "\n";
		std::cout << "P2 score: " << player2.getScore() << "\n";
		glfwSetWindowShouldClose(m_window.getWindow(), true);
	}
	if (player2.getScore() == 15)
	{
		std::cout << "PLAYER 2 WIN\n";
		std::cout << "P1 score: " << player1.getScore() << "\n";
		std::cout << "P2 score: " << player2.getScore() << "\n";
		glfwSetWindowShouldClose(m_window.getWindow(), true);
	}
}