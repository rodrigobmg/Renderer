#pragma once

#include <General/Application/ApplicationBase.h>
#include <General/Graphics/PointLight.h>

class Application : public ApplicationBase
{
public:
	Application(HINSTANCE hInstance, int windowWidth, int windowHeight, const char* name);
	~Application();
	virtual void Render() override;
	virtual void Update() override;
	void MoveCamera(int x, int y);
	void RotateLight(int x, int y);
	void RotateObject();

private:
	ScenePtr		m_scene;
	SceneNodePtr	m_camera;
	int				m_mousePosX;
	int				m_mousePosY;
	bool			m_firstMouseMove;
};
