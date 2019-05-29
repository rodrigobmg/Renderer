#include "GLGraphics.h"

#include <Externals/GLAD/Includes.h>
#include <Externals/GLFW/Includes.h>
#include <General/Logger.h>

bool GLGraphics::Initialize(int screenWidth, int screenHeight, bool vsync, const IWindow * window, bool fullscreen, float screenDepth, float screenNear)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		LOG("Failed to initialize GLAD");
		return false;
	}
	glViewport(0, 0, screenWidth, screenHeight);
	return true;
}

void GLGraphics::Render(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLGraphics::Shutdown()
{
}
