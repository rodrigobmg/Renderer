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
	WindowPtr		m_window;
	GraphicsPtr		m_graphics;
	SceneObjectPtr	m_object;
	bool			m_ready;
};
