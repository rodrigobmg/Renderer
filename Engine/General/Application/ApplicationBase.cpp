#include "pch.h"
#include "ApplicationBase.h"

#include "Window.h"
#include "Input.h"

#include <Directx11/Graphics/DX11Graphics.h>

ApplicationBase::ApplicationBase(HINSTANCE hInstance, int windowWidth, int windowHeight, const char* name, bool vsyncEnabled, bool fullscreen, float screenNear, float screenDepth)
	: m_window(nullptr)
	, m_graphics(nullptr)
	, m_ready(false)
{
	assert(!m_window);
	m_window.reset(new Window(hInstance, windowWidth, windowHeight, name));
	m_graphics.reset(new DX11Graphics());
	m_ready = m_graphics->Initialize(m_window, windowWidth, windowHeight, vsyncEnabled, fullscreen, screenDepth, screenNear);
}

ApplicationBase::~ApplicationBase()
{
	if (m_graphics)
	{
		m_graphics->Shutdown();
	}
}

void ApplicationBase::Run()
{
	assert(m_ready);
	m_timer.Reset();
	while (!m_window->Closed())
	{
		Update();
		Render();
	}
}

void ApplicationBase::Update()
{
	assert(m_ready);
	m_timer.Tick();
	m_window->ProcessInputs();
	if (Input::GetKeyDown(Input::KEY_ESC))
	{
		m_window->Close();
	}
}
