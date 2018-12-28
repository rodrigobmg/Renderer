#pragma once

#include <General/IWindow.h>

struct GLFWwindow;

class GLFWindow : public IWindow
{
public:
	GLFWindow(int windowWidth, int windowHeight, const char* name);
	~GLFWindow();
	virtual bool Closed() const override;
	virtual void ProcessInputs() override;
	virtual void SwapBuffers() override;

private:
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void ProcessKeyboardInput(GLFWwindow* window);
	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	GLFWwindow*	m_window;
};