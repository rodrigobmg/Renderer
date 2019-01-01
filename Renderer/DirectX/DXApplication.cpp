#include "DXApplication.h"

#include "DXWindow.h"

#include <General/Input.h>
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
		Update();
		m_window->SwapBuffers();
	}
}

void DXApplication::Update()
{
	if (Input::GetKeyDown(Input::KEY_ESC))
	{
		m_window->Close();
	}
}
