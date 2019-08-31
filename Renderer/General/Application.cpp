#include "Application.h"

#include "Input.h"
#include "Object.h"

#ifdef DIRECTX11
#include <Directx11/DX11Window.h>
#include <Directx11/DX11Graphics.h>
#elif OPENGL
#include <Opengl/GLWindow.h>
#include <Opengl/GLGraphics.h>
#endif

const bool kFullscreen = false;
const bool kVsyncEnabled = true;
const float kScreenDepth = 1000.0f;
const float kScreenNear = 0.1f;

Application::Application(int windowWidth, int windowHeight, const char* name)
	:m_ready(false)
{
	assert(!m_window);
#ifdef DIRECTX11
	m_window = new DX11Window(windowWidth, windowHeight, name);
	m_graphics = new DX11Graphics();
#elif OPENGL
	m_window = new GLWindow(windowWidth, windowHeight, name);
	m_graphics = new GLGraphics();
#endif
	m_ready = m_graphics->Initialize(windowWidth, windowHeight, kVsyncEnabled, m_window, kFullscreen, kScreenDepth, kScreenNear);

	SharedPtr<Core::Object> object = m_graphics->CreateObject("Assets/Models/cube.glb", "Assets/DirectX/Shaders/color.vs", "Assets/DirectX/Shaders/color.ps");
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
