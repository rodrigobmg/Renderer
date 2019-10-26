#pragma once

#include <General/Application/ApplicationBase.h>

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
	SceneObjectPtr	m_object;
	IPointLightPtr	m_pointLight;
	ICameraPtr		m_camera;
	int				m_mousePosX;
	int				m_mousePosY;
	bool			m_firstMouseMove;
};
