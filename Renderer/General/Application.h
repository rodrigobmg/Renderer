#pragma once

#include"IApplication.h"

class IWindow;
class IGraphics;
class Application : public IApplication
{
public:
	Application(int windowWidth, int windowHeight, const char* name);
	~Application();
	virtual void Run() override;
	virtual void Update() override;

private:
	IWindow*	m_window;
	IGraphics*	m_graphics;
};
