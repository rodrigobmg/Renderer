#pragma once

#include <General/IWindow.h>
#include <windows.h>

class DXWindow : public IWindow
{
public:
	DXWindow(int windowWidth, int windowHeight, const char* name);
	DXWindow(DXWindow& other) = delete;
	DXWindow& operator=(DXWindow& other) = delete;
	~DXWindow();

	virtual bool Closed() const override;
	virtual void ProcessInputs() override;
	virtual void SwapBuffers() override;
	virtual void Close() override;

	HWND GetHandle() const { return m_hwnd; }

private:
	static LRESULT CALLBACK HandleWindowMessages(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

	LPCSTR		m_applicationName;
	HINSTANCE	m_hinstance;
	HWND		m_hwnd;
	MSG			m_msg;
};