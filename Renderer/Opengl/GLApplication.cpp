#include "GLApplication.h"

#include "GLWindow.h"
#include <cassert>

IWindow* GLApplication::m_window = nullptr;

GLApplication::GLApplication(int windowHeight, int windowWidth, const char* name)
{
	assert(!m_window);
	m_window = new GLWindow(windowHeight, windowWidth, name);
	assert(m_window);
}

GLApplication::~GLApplication()
{
	delete m_window;
}

void GLApplication::Run()
{
	while (!m_window->Closed())
	{
		m_window->ProcessInputs();
		m_window->SwapBuffers();
	}
}
