#include "Application.h"

#include <General/Input.h>
#include <DirectX/DXWindow.h>
#include <Opengl/GLWindow.h>
#include <cassert>

IWindow* Application::m_window = nullptr;

Application::Application(int windowWidth, int windowHeight, const char* name)
{
	assert(!m_window);
#ifdef DIRECTX
	m_window = new DXWindow(windowWidth, windowHeight, name);
#elif OPENGL
	m_window = new GLWindow(windowWidth, windowHeight, name);
#else
#error Unsupported platform
#endif // DIRECTX
	assert(m_window);
}

Application::~Application()
{
	delete m_window;
}

void Application::Run()
{
	while (!m_window->Closed())
	{
		m_window->ProcessInputs();
		Update();
		m_window->SwapBuffers();
	}
}

void Application::Update()
{
	if (Input::GetKeyDown(Input::KEY_ESC))
	{
		m_window->Close();
	}
}
