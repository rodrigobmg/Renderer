#include "pch.h"
#include "Application.h"

#include <General/Application/Input.h>
#include <General/Application/IWindow.h>
#include <General/Graphics/SceneObject.h>
#include <General/Graphics/PointLight.h>
#include <General/Graphics/Loader.h>
#include <General/Graphics/ICamera.h>
#include <General/Graphics/IGraphics.h>
#include <General/Math/Color.h>
#include <General/Math/Vector3d.h>
#include <General/Math/Math.h>
#include <General/Math/Transform.h>

const bool kFullscreen = false;
const bool kVsyncEnabled = true;
const float kScreenDepth = 1000.0f;
const float kScreenNear = 0.1f;

Application::Application(HINSTANCE hInstance, int windowWidth, int windowHeight, const char* name)
	: ApplicationBase(hInstance, windowWidth, windowHeight, name, kVsyncEnabled, kFullscreen, kScreenNear, kScreenDepth)
	, m_mousePosX(0)
	, m_mousePosY(0)
	, m_firstMouseMove(true)
{
	if (!m_ready)
	{
		return;
	}

	m_camera = m_graphics->CreateCamera();
	if (!m_camera)
	{
		m_ready = false;
		return;
	}

	m_object = Loader::LoadModel("Assets/cube.object", m_graphics);
	if (!m_object)
	{
		m_ready = false;
		return;
	}
	m_object->m_transform.m_scale *= 0.2f;

	m_pointLight.reset(new PointLight(Color(1.0f, 1.0f, 1.0f, 1.0f), Vector3d(0.0f, 0.0f, -50.0f), m_graphics));
	if (!m_pointLight)
	{
		m_ready = false;
		return;
	}

	assert(m_window);
}

Application::~Application()
{
	//Explicitly release pointer so that all graphics resources are destroyed before graphics is shut down
	m_object.reset();
	m_pointLight.reset();
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

static const float kMousMoveMultiplier = Math::DEG2RAD * 10000.0f;
void Application::Update()
{
	ApplicationBase::Update();

	RotateObject();

	int x, y;
	Input::GetMousePosition(x, y);
	if (m_firstMouseMove)
	{
		m_firstMouseMove = false;
		m_mousePosX = x;
		m_mousePosY = y;
	}
	
	if(Input::GetMouseButtonDown(Input::MouseButtonType::kRight))
	{
		RotateLight(x, y);
	}

	MoveCamera(x, y);

	m_mousePosX = x;
	m_mousePosY = y;
}

static const float kCameraSpeed = 100.0f;
void Application::MoveCamera(int x, int y)
{
	float deltaTime = m_timer.GetDeltaTime();
	Transform cameraTransform = m_camera->GetTransform();
	if (Input::GetMouseButtonDown(Input::MouseButtonType::kLeft))
	{
		float deltaX = (x - m_mousePosX) / static_cast<float>(m_window->GetWindowWidth());
		float deltaY = (y - m_mousePosY) / static_cast<float>(m_window->GetWindowHeight());

		Quaternion deltaRotation(Vector3d(kMousMoveMultiplier * deltaY, kMousMoveMultiplier * deltaX, 0.f) * deltaTime);
		cameraTransform.m_orientation = deltaRotation * cameraTransform.m_orientation;
	}

	Vector3d forward = Vector3d::kForward * cameraTransform.m_orientation;
	forward *= deltaTime * kCameraSpeed;
	Vector3d side = Vector3d::kSide * cameraTransform.m_orientation;
	side *= deltaTime * kCameraSpeed;
	if (Input::GetKeyDown(Input::Keys::KEY_W))
	{
		cameraTransform.m_position += forward;
	}
	if (Input::GetKeyDown(Input::Keys::KEY_S))
	{
		cameraTransform.m_position -= forward;
	}
	if (Input::GetKeyDown(Input::Keys::KEY_A))
	{
		cameraTransform.m_position -= side;
	}
	if (Input::GetKeyDown(Input::Keys::KEY_D))
	{
		cameraTransform.m_position += side;
	}
	m_camera->SetTransform(cameraTransform);
}

void Application::RotateLight(int x, int y)
{
	float deltaTime = m_timer.GetDeltaTime();
	float deltaX = (x - m_mousePosX) / static_cast<float>(m_window->GetWindowWidth());
	float deltaY = (y - m_mousePosY) / static_cast<float>(m_window->GetWindowHeight());

	Quaternion deltaRotation(Vector3d(kMousMoveMultiplier * deltaY, kMousMoveMultiplier * deltaX, 0.f) * deltaTime);
	const Quaternion& lightRotation = m_pointLight->GetRotationAroundOrigin();
	m_pointLight->SetRotationAroundOrigin(deltaRotation * lightRotation);
}

void Application::RotateObject()
{
	float deltaTime = m_timer.GetDeltaTime();
	Vector3d delta;
	if (Input::GetKeyDown(Input::KEY_UP))
	{
		delta.x = Math::DEG2RAD;
	}
	if (Input::GetKeyDown(Input::KEY_DOWN))
	{
		delta.x = -Math::DEG2RAD;
	}
	if (Input::GetKeyDown(Input::KEY_LEFT))
	{
		delta.y = Math::DEG2RAD;
	}
	if (Input::GetKeyDown(Input::KEY_RIGHT))
	{
		delta.y = -Math::DEG2RAD;
	}
	if (Input::GetKeyDown(Input::KEY_R))
	{
		m_object->m_transform.m_orientation = Quaternion();
	}

	m_object->m_transform.m_orientation *= Quaternion(delta * deltaTime);
}
