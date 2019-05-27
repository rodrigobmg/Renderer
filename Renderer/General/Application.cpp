#include "Application.h"

#include <General/Input.h>

#include <DirectX/DXWindow.h>
#include <DirectX/DXGraphics.h>

#include <Opengl/GLWindow.h>

#include <cassert>

const bool kFullscreen = false;
const bool kVsyncEnabled = true;
const float kScreenDepth = 1000.0f;
const float kScreenNear = 0.1f;

Application::Application(int windowWidth, int windowHeight, const char* name)
	:m_ready(false)
{
	assert(!m_window);
#ifdef DIRECTX
	m_window = new DXWindow(windowWidth, windowHeight, name);
	m_ready = m_window != nullptr;
	m_graphics = new DXGraphics();
	m_ready &= m_graphics->Initialize(windowWidth, windowHeight, kVsyncEnabled, m_window, kFullscreen, kScreenDepth, kScreenNear);
#elif OPENGL
	m_window = new GLWindow(windowWidth, windowHeight, name);
	m_graphics = nullptr;
#else
#error Unsupported platform
#endif // DIRECTX
	assert(m_window);
}

Application::~Application()
{
	if (m_window)
	{
		delete m_window;
	}
	if (m_graphics)
	{
		delete m_graphics;
	}
}

void Application::Run()
{
	assert(m_ready);
	while (!m_window->Closed())
	{
		m_window->ProcessInputs();
		Update();
		if (m_graphics)
		{
			m_graphics->Render(0.5f, 0.5f, 0.5f, 1.0f);
		}
		m_window->SwapBuffers();
	}
}

void Application::Update()
{
	assert(m_ready);
	if (Input::GetKeyDown(Input::KEY_ESC))
	{
		m_window->Close();
	}
}
