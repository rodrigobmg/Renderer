#include "GLWindow.h"

#include <Externals/GLFW/Includes.h>
#include <General/Logger.h>
#include <General/Input.h>
#include <assert.h>

GLWindow::GLWindow(int windowWidth, int windowHeight, const char* name)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	m_window = glfwCreateWindow(windowWidth, windowHeight, name, NULL, NULL);
	if (m_window == NULL) {
		LOG("Failed to create GLFW window");
		glfwTerminate();
		assert(false);
	}
	
	glfwMakeContextCurrent(m_window);

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
 	glfwSetCursorPosCallback(m_window, MouseCallback);
 	glfwSetScrollCallback(m_window, ScrollCallback);
	glfwSetKeyCallback(m_window, KeyCallback);
	glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallback);
}

GLWindow::~GLWindow()
{
	//Shutdown input
	Input::Shutdown();
	glfwTerminate();
}

bool GLWindow::Closed() const
{
	return glfwWindowShouldClose(m_window);
}

void GLWindow::ProcessInputs()
{
	glfwPollEvents();
}

void GLWindow::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}

void GLWindow::Close()
{
	glfwSetWindowShouldClose(m_window, true);
}

void GLWindow::MouseCallback(GLFWwindow * window, double xpos, double ypos)
{
}

void GLWindow::ScrollCallback(GLFWwindow * window, double xoffset, double yoffset)
{
}

void GLWindow::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		Input::SetKeyDown(static_cast<unsigned int>(key));
	}
	else if (action == GLFW_RELEASE)
	{
		Input::SetKeyUp(static_cast<unsigned int>(key));
	}
}

void GLWindow::FrameBufferSizeCallback(GLFWwindow * window, int width, int height)
{
	
}
