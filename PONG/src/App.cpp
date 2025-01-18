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
	aspect = (float)m_window.getWidth() / (float)m_window.getHeight();

	shader.CompileShader("src/render/shaders/shader.vert", "src/render/shaders/shader.frag");
	
	ui.init();

	player1.init();
	player1.setPosition(glm::vec3(-1.5,0.0,0.0));

	player2.init();
	player2.setPosition(glm::vec3(1.5, 0.0, 0.0));

	projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
}

void App::run()
{
	while (!glfwWindowShouldClose(m_window.getWindow()))
	{
		float currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;

		//glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		input(m_window.getWindow());
		

		//update
		player1.OnUpdate();
		player2.OnUpdate();
		
		//render
		shader.use();
		shader.setMat4("projection", projection);

		ui.middleLine(shader);

		player1.render(shader);
		player2.render(shader);

		m_window.OnUpdate();
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


void App::chectCollision()
{
}

void App::close()
{
	m_window.TerminateWindow();
	glfwTerminate();
}
