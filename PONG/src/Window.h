#pragma once

#include<iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Window
{
public:
	Window();
	~Window();
	void TerminateWindow();

	int getWidth();
	int getHeight();
	bool getVSync();
	GLFWwindow* getWindow();

	void setVSync(bool x);

	void OnUpdate();
	void createWindow();
private:
	GLFWwindow* m_window;

	struct WindowData
	{
		const char* title;
		int width;
		int height;
		bool VSync;
	};
	WindowData m_Data;
};

