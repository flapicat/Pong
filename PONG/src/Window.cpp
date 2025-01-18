#include "Window.h"

Window::Window()
{

}

Window::~Window()
{
	TerminateWindow();
}

void Window::TerminateWindow()
{
	glfwDestroyWindow(m_window);
}

int Window::getWidth()
{
	return m_Data.width;
}

int Window::getHeight()
{
	return m_Data.height;
}

bool Window::getVSync()
{
	return m_Data.VSync;
}

GLFWwindow* Window::getWindow()
{
	return m_window;
}

void Window::setVSync(bool x)
{
	glfwSwapInterval(x);
}

void Window::OnUpdate()
{
	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

void Window::createWindow()
{
	m_Data.width = 1280;
	m_Data.height = 720;
	m_Data.title = "PONG";
	m_Data.VSync = true;
	
	m_window = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title, NULL, NULL);
	glfwMakeContextCurrent(m_window);
}


