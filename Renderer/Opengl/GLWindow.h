#pragma once

#include <General/IWindow.h>

struct GLFWwindow;

class GLWindow : public IWindow
{
public:
	GLWindow(int windowWidth, int windowHeight, const char* name);
	~GLWindow();
	virtual bool Closed() const override;
	virtual void ProcessInputs() override;
	virtual void SwapBuffers() override;
	virtual void Close() override;

private:
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	GLFWwindow*	m_window;
};