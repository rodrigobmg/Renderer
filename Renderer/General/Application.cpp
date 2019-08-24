#include "Application.h"

#include "Input.h"
#include "Object.h"

#ifdef DIRECTX
#include <DirectX/DXWindow.h>
#include <DirectX/DXGraphics.h>
#elif OPENGL
#include <Opengl/GLWindow.h>
#include <Opengl/GLGraphics.h>
#else
#error Unsupported platform
#endif

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
	m_graphics = new DXGraphics();
#elif OPENGL
	m_window = new GLWindow(windowWidth, windowHeight, name);
	m_graphics = new GLGraphics();
#else
#error Unsupported platform
#endif
	m_ready = m_graphics->Initialize(windowWidth, windowHeight, kVsyncEnabled, m_window, kFullscreen, kScreenDepth, kScreenNear);

	std::shared_ptr<Core::Object> object = m_graphics->CreateObject("teapot.glb", "Shaders/color.vs", "Shaders/color.ps");
	m_ready &= object != nullptr;
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
		m_graphics->Shutdown();
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
		Render();
		m_window->SwapBuffers();
	}
}

void Application::Render()
{
	if (m_graphics)
	{
		m_graphics->Render();
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