#pragma once
#include <General/IApplication.h>
#include <string>

class IWindow;
class GLApplication : public IApplication
{
public:
	GLApplication(int windowHeight, int windowWidth, const char* name);
	~GLApplication();
	virtual void Start() override;

private:
	static IWindow*	m_window;
};