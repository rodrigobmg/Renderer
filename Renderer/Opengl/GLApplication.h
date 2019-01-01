#pragma once
#include <General/IApplication.h>
#include <string>

class IWindow;
class GLApplication : public IApplication
{
public:
	GLApplication(int windowHeight, int windowWidth, const char* name);
	GLApplication(GLApplication& other) = delete;
	GLApplication& operator=(GLApplication& other) = delete;
	~GLApplication();

	virtual void Run() override;

private:
	virtual void Update() override;

	static IWindow*	m_window;
};