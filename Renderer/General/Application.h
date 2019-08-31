#pragma once

#include"IApplication.h"

class IWindow;
class IGraphics;
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
	IWindow*	m_window;
	IGraphics*	m_graphics;
	bool		m_ready;
};
