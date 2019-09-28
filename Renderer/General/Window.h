#pragma once

#include "IWindow.h"
#include <windows.h>

class Window : public IWindow
{
public:
	Window(HINSTANCE hInstance, int windowWidth, int windowHeight, const char* name);
	Window(Window& other) = delete;
	Window& operator=(Window& other) = delete;
	~Window();

	virtual bool Closed() const override;
	virtual void ProcessInputs() override;
	virtual void Close() override;
	virtual HWND GetHandle() const override { return m_hwnd; }
	virtual int GetWindowWidth() const override { return m_windowWidth; }
	virtual int GetWindowHeight() const override { return m_windowHeight; }

private:
	void CaptureMouse();
	void ReleaseMouse();
	static LRESULT CALLBACK HandleWindowMessages(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

	static Window*	s_instance;
	LPCSTR			m_applicationName;
	HINSTANCE		m_hinstance;
	HWND			m_hwnd;
	MSG				m_msg;
	int				m_windowWidth;
	int				m_windowHeight;
};