#pragma once

#include <General/IApplication.h>

class IWindow;
class DXApplication : public IApplication
{
public:
	DXApplication(int windowWidth, int windowHeight, const char* name);
	~DXApplication();
	virtual void Run() override;
	virtual void Update() override;

private:
	static IWindow* m_window;
};