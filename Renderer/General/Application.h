#pragma once

#include"IApplication.h"

class Application : public IApplication
{
public:
	Application(HINSTANCE hInstance, int windowWidth, int windowHeight, const char* name);
	~Application();
	virtual void Run() override;
	void Render();
	virtual void Update() override;
	virtual bool IsReady() const override { return m_ready; }

private:
	IWindowPtr		m_window;
	IGraphicsPtr	m_graphics;
	SceneObjectPtr	m_object;
	IPointLightPtr	m_pointLight;
	int				m_mousePosX;
	int				m_mousePosY;
	bool			m_firstMouseMove;
	bool			m_ready;
};
