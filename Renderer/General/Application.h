#pragma once

#include"IApplication.h"

class IWindow;
class Application : public IApplication
{
public:
	Application(int windowWidth, int windowHeight, const char* name);
	~Application();
	virtual void Run() override;
	virtual void Update() override;

private:
	static IWindow*	m_window;
};
