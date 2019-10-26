#pragma once

#include "IApplication.h"
#include "Timer.h"

class ApplicationBase : public IApplication
{
public:
	ApplicationBase(HINSTANCE hInstance, int windowWidth, int windowHeight, const char* name, bool vsyncEnabled, bool fullscreen, float screenNear, float screenDepth);
	~ApplicationBase();

	ApplicationBase(const ApplicationBase&) = delete;

	virtual void Run() override;
	virtual bool IsReady() const override { return m_ready; }

	virtual void Update();
	virtual void Render() = 0;

protected:
	IWindowPtr		m_window;
	IGraphicsPtr	m_graphics;
	Timer			m_timer;
	bool			m_ready;
};