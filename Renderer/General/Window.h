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
	virtual void SwapBuffers() override;
	virtual void Close() override;
	virtual HWND GetHandle() const override { return m_hwnd; }

private:
	static LRESULT CALLBACK HandleWindowMessages(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

	LPCSTR		m_applicationName;
	HINSTANCE	m_hinstance;
	HWND		m_hwnd;
	MSG			m_msg;
};