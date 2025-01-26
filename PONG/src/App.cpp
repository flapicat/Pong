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
	
	//WINDOW
	m_window.createWindow();
	if (m_window.getWindow() == NULL)
	{
		std::cout << "FAILED TO CREATE WINDOW\n";
		glfwTerminate();
		exit(-1);
	}

	//GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "FAILED TO INIT GLAD\n";
		exit(-1);
	}

	//GL ENABLE
	glEnable(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//TEXT INIT
	shaderText.CompileShader("shaders/Text.vert", "shaders/Text.frag");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_window.getWidth()), 0.0f, static_cast<float>(m_window.getHeight()));
	shaderText.use();
	glUniformMatrix4fv(glGetUniformLocation(shaderText.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	ScoreText.init("res/font/Orange Kid.otf", 250);
	infoText.init("res/font/Orange Kid.otf", 50);

	//GAME OBJECTS INIT
	shader.CompileShader("shaders/shader.vert", "shaders/shader.frag");
	
	ui.init();

	ball.init();

	player1.init();
	player1.setPosition(glm::vec3(-1.5,0.0,0.0));

	player2.init();
	player2.setPosition(glm::vec3(1.5, 0.0, 0.0));

	//PROJECTION INIT
	m_aspect = (float)m_window.getWidth() / (float)m_window.getHeight();
	m_projection = glm::ortho(-m_aspect, m_aspect, -1.0f, 1.0f, -1.0f, 1.0f);
}

void App::run()
{
	while (!glfwWindowShouldClose(m_window.getWindow()))
	{
		//DELTA TIME
		float currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;

		//CLEAR
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//GAME
		input(m_window.getWindow());

		if (m_gameEnd == true)
		{
			//INFO RENDER
			infoText.RenderText(shaderText, "PRESS ESC TO QUIT", 10, m_window.getHeight() - 50, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
			infoText.RenderText(shaderText, "PRESS R TO RESET", 10, m_window.getHeight() - 100, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

			//WHICH PLAYER WIN RENDER
			if (player1.getScore() > player2.getScore())
				ScoreText.RenderText(shaderText, "PLAYER 1 WIN", m_window.getWidth() / 7, m_window.getHeight() / 2, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
			if (player1.getScore() < player2.getScore())
				ScoreText.RenderText(shaderText, "PLAYER 2 WIN", m_window.getWidth() / 7, m_window.getHeight() / 2, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		else
		{

			if (m_StartTimerCount == true)
			{
				m_StartTimer -= m_deltaTime;
				if (m_StartTimer <= 0)
					m_StartTimerCount = false;
				else
				{
					char StartTimer[2];
					itoa((int)m_StartTimer, StartTimer, 10);
					ScoreText.RenderText(shaderText, StartTimer, m_window.getWidth() / 2 - 50, m_window.getHeight() / 2 - 50, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
				}
			}
			else
			{
				//UPDATE
				ball.OnUpdate(m_deltaTime);
			}

			//UPDATE
			player1.windowCollision();
			player2.windowCollision();

			//RENDER
			shader.use();
			shader.setMat4("projection", m_projection);

			ui.middleLine(shader);
			player1.render(shader);
			player2.render(shader);
			ball.render(shader);
			renderText();
		}

		m_window.OnUpdate();
		GameLogic();
	}
}

void App::input(GLFWwindow* window)
{
	//BASIC LOGIC
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		m_gameEnd = true;
		glfwSetWindowShouldClose(window, true);
	}
	if (m_gameEnd == true)
	{
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			//LOGIC
			m_gameEnd = false;
			m_StartTimerCount = true;
			m_StartTimer = 3.99;

			//PLAYER 1
			player1.setPosition(glm::vec3(-1.5,0,0));
			player1.setScore(0);
			//PLAYER 2
			player2.setPosition(glm::vec3(1.5, 0, 0));
			player2.setScore(0);
		}
	}

	//PLAYER 1 INPUT
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		player1.processInput(UP, m_deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		player1.processInput(DOWN, m_deltaTime);
	}

	//DEV INPUT
	// 
	//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	//{
	//	player1.processInput(LEFT, m_deltaTime);
	//}
	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//{
	//	player1.processInput(RIGHT, m_deltaTime);
	//}

	//PLAYER2 2 INPUT
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
	//-------------------------------------------------
	// ORGINAL COLLISION
	// ------------------------------------------------
	//bool collisionX = ball->getPosition().x + ball->m_height/2 >= player->getPosition().x - player->m_width /2 &&
	//	              player->getPosition().x + player->m_width/2 >= ball->getPosition().x - ball->m_height /2;
	//
	//bool collisionY = ball->getPosition().y + ball->m_height/2 >= player->getPosition().y - player->m_height /2 &&
	//	              player->getPosition().y + player->m_height/2 >= ball->getPosition().y - ball->m_height /2;
	//
	//if (collisionX && collisionY)
	//{
	//	m_count = true;
	//	ball->swapVelX();
	//	std::cout << "BOUNCE\n";
	//}

	//-------------------------------------------------
	// ACTUAL COLLISION
	// ------------------------------------------------
	
	//top half player collision
	bool collisionTopX = ball->getPosition().x + ball->getHeight() / 2 >= player->getPosition().x - player->m_width &&
		player->getPosition().x + player->m_width >= ball->getPosition().x - ball->getHeight() / 2;

	bool collisionTopY = ball->getPosition().y + ball->getHeight() / 2 >= player->getPosition().y + player->m_height / 8 &&
		player->getPosition().y + player->m_height / 2 >= ball->getPosition().y - ball->getHeight() / 2;

	if (collisionTopX && collisionTopY)
	{
		m_BPcolCount = true;
		ball->swapVelX();
		ball->setVelY(1);
		return;
	}

	//bottom half player colision
	bool collisionBotX = ball->getPosition().x + ball->getHeight() / 2 >= player->getPosition().x - player->m_width &&
		player->getPosition().x + player->m_width >= ball->getPosition().x - ball->getHeight() / 2;

	bool collisionBotY = ball->getPosition().y + ball->getHeight() / 2 >= player->getPosition().y - player->m_height / 2 &&
		player->getPosition().y + player->m_height / 8 >= ball->getPosition().y - ball->getHeight() / 8;

	if (collisionBotX && collisionBotY)
	{
		m_BPcolCount = true;
		ball->swapVelX();
		ball->setVelY(-1);
		return;
	}
}

void App::renderText()
{
	//PLAYER 1 POINTS
	char Player1Points[32];
	itoa(player1.getScore(), Player1Points, 10);
	ScoreText.RenderText(shaderText, Player1Points, m_window.getWidth() / 4, (m_window.getHeight() / 5) * 4, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	//PLAYER 2 POINTS
	char Player2Points[32];
	itoa(player2.getScore(), Player2Points, 10);
	ScoreText.RenderText(shaderText, Player2Points, (m_window.getWidth() / 4) * 3, (m_window.getHeight() / 5) * 4, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

}

void App::close()
{
	//IT ONLY LOOKS GOOD BUT DOES ALMOST NOTHING 
	m_window.TerminateWindow();
	glfwTerminate();
}

void App::GameLogic()
{
	//-------------------------------------------------
	//BALL-PLAYER COLLISION
	//-------------------------------------------------
	if (m_BPcolCount == true)
	{
		m_BPcolTimer += m_deltaTime;
		if (m_BPcolTimer > 0.2)
		{
			m_BPcolCount = false;
			m_BPcolTimer = 0;
		}
	}
	if (m_BPcolTimer == 0)
	{
		chectCollision(&ball, &player1);
		chectCollision(&ball, &player2);
	}

	//-------------------------------------------------
	//BALL-WINDOW COLLISION
	//-------------------------------------------------
	if (m_WindowColCount == true)
	{
		m_WindowColTimer += m_deltaTime;
		if (m_WindowColTimer > 1)
		{
			m_WindowColCount = false;
			m_WindowColTimer = 0;
		}
	}
	if (m_WindowColTimer == 0)
	{
		ball.windowCollision();
	}

	//-------------------------------------------------
	//ADD SCORE
	//-------------------------------------------------
	if (ball.getLeftCol())
	{
		player1.addScore();
		ball.setLeftCol(false);
	}
	if (ball.getRightCol())
	{
		player2.addScore();
		ball.setRightCol(false);
	}

	//-------------------------------------------------
	//END GAME CHECK
	//-------------------------------------------------
	if (player1.getScore() == 15)
	{
		m_gameEnd = true;
	}
	if (player2.getScore() == 15)
	{
		m_gameEnd = true;
	}
}

//TODO:
//REDUSE USLESS VARIABLES AND FUNCTIONS REDUSE GLOBALS
//CREATE BUILD SYSTEM THAT LINK EVERY LIBRARY AND HEADERS, ALSO NEED TO COPY SHADERS AND RESOURSE FOLDERS TO BINARY FOLDER