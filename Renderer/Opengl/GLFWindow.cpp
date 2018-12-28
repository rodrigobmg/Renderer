#include "GLFWindow.h"

#include <Externals/GLAD/Includes.h>
#include <Externals/GLFW/Includes.h>
#include <General/Logger.h>
#include <assert.h>

GLFWindow::GLFWindow(int windowWidth, int windowHeight, const char* name)
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
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		LOG("Failed to initialize GLAD");
		assert(false);
	}

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
 	glfwSetCursorPosCallback(m_window, MouseCallback);
 	glfwSetScrollCallback(m_window, ScrollCallback);
	glViewport(0, 0, windowWidth, windowHeight);
	glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallback);
}

GLFWindow::~GLFWindow()
{
	glfwTerminate();
}

bool GLFWindow::Closed() const
{
	return glfwWindowShouldClose(m_window);
}

void GLFWindow::ProcessInputs()
{
	ProcessKeyboardInput(m_window);
	glfwPollEvents();
}

void GLFWindow::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}

void GLFWindow::MouseCallback(GLFWwindow * window, double xpos, double ypos)
{
}

void GLFWindow::ScrollCallback(GLFWwindow * window, double xoffset, double yoffset)
{
}

void GLFWindow::ProcessKeyboardInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void GLFWindow::FrameBufferSizeCallback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}
