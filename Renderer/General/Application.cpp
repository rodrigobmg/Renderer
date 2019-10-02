#include "stdafx.h"
#include "Application.h"

#include "Input.h"
#include "SceneObject.h"
#include "Window.h"
#include "PointLight.h"

#include <Directx11/DX11Graphics.h>
#include <General/Loader.h>

const bool kFullscreen = false;
const bool kVsyncEnabled = true;
const float kScreenDepth = 1000.0f;
const float kScreenNear = 0.1f;

Application::Application(HINSTANCE hInstance, int windowWidth, int windowHeight, const char* name)
	: m_mousePosX(0)
	, m_mousePosY(0)
	, m_firstMouseMove(true)
	, m_ready(false)
{
	assert(!m_window);
	m_window.reset(new Window(hInstance, windowWidth, windowHeight, name));
	m_graphics.reset(new DX11Graphics());
	m_ready = m_graphics->Initialize(m_window, windowWidth, windowHeight, kVsyncEnabled, kFullscreen, kScreenDepth, kScreenNear);

	m_object = Loader::LoadModel("Assets/cube.object", m_graphics);

	if (!m_object)
	{
		m_ready &= false;
	}

	if (m_object)
	{
		m_object->m_transform.m_scale *= 0.2f;
	}

	m_pointLight.reset(new PointLight(Color(1.0f), Vector3d(-10.0f, 10.0f, -50.0f), m_graphics));
	if (!m_pointLight)
	{
		m_ready &= false;
	}

	assert(m_window);
}

Application::~Application()
{
	//Explicitly release pointer so that all graphics resources are destroyed before graphics is shut down
	m_object.reset();
	m_pointLight.reset();

	if (m_graphics)
	{
		m_graphics->Shutdown();
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
	}
}

void Application::Render()
{
	if (m_graphics)
	{
		vector<IPointLightPtr> lights(1, m_pointLight);
		m_graphics->StartRender(lights);
		m_object->Render();
		m_pointLight->Render();
		m_graphics->EndRender();
	}
}

void Application::Update()
{
	assert(m_ready);
	if (Input::GetKeyDown(Input::KEY_ESC))
	{
		m_window->Close();
	}

	if (Input::GetKeyDown(Input::KEY_UP))
	{
		Vector3d delta(Math::DEG2RAD, 0.0f, 0.0f);
		m_object->m_transform.m_orientation *= Quaternion(delta);
	}
	if (Input::GetKeyDown(Input::KEY_DOWN))
	{
		Vector3d delta(-Math::DEG2RAD, 0.0f, 0.0f);
		m_object->m_transform.m_orientation *= Quaternion(delta);
	}
	if (Input::GetKeyDown(Input::KEY_LEFT))
	{
		Vector3d delta(0.0f, Math::DEG2RAD, 0.0f);
		m_object->m_transform.m_orientation *= Quaternion(delta);
	}
	if (Input::GetKeyDown(Input::KEY_RIGHT))
	{
		Vector3d delta(0.0f, -Math::DEG2RAD, 0.0f);
		m_object->m_transform.m_orientation *= Quaternion(delta);
	}
	if (Input::GetKeyDown(Input::KEY_R))
	{
		m_object->m_transform.m_orientation = Quaternion();
	}

	int x, y;
	Input::GetMousePosition(x, y);


	if (m_firstMouseMove)
	{
		m_firstMouseMove = false;
	}

	m_mousePosX = x;
	m_mousePosY = y;
}
