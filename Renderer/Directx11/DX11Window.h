#pragma once

#include <General/IWindow.h>
#include <windows.h>

class DX11Window : public IWindow
{
public:
	DX11Window(int windowWidth, int windowHeight, const char* name);
	DX11Window(DX11Window& other) = delete;
	DX11Window& operator=(DX11Window& other) = delete;
	~DX11Window();

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