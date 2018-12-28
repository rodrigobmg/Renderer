#include "DXApplication.h"
#include "DXWindow.h"

#include <cassert>

IWindow* DXApplication::m_window = nullptr;

DXApplication::DXApplication(int windowWidth, int windowHeight, const char* name)
{
	assert(!m_window);
	m_window = new DXWindow(windowWidth, windowHeight, name);
	assert(m_window);
}

DXApplication::~DXApplication()
{
	delete m_window;
}

void DXApplication::Run()
{
	while (!m_window->Closed())
	{
		m_window->ProcessInputs();
		m_window->SwapBuffers();
	}
}
