#include "DXWindow.h"

#include <General/Logger.h>
#include <cassert>

DXWindow::DXWindow(int windowWidth, int windowHeight, const char* name)
{
	WNDCLASSEX wc;
	int posX, posY;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);
	LOG("Error: %d", GetLastError());

	// Give the application a name.
	m_applicationName = name;

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = HandleWindowMessages;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = name;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Place the window in the middle of the screen.
	posX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
	posY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		NULL,
		posX, posY, windowWidth, windowHeight, NULL, NULL, m_hinstance, NULL);
	assert(m_hwnd);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(false);
}

DXWindow::~DXWindow()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;
}

bool DXWindow::Closed() const
{
	return m_msg.message == WM_QUIT;
}

void DXWindow::ProcessInputs()
{
	ZeroMemory(&m_msg, sizeof(MSG));
	if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
	}
}

void DXWindow::SwapBuffers()
{
}

LRESULT CALLBACK DXWindow::HandleWindowMessages(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
	// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// All other messages pass to the message handler in the system class.
	default:
	{
		return DefWindowProc(hwnd, umessage, wparam, lparam);
	}
	}
}
