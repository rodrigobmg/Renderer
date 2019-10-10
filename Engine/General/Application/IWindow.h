#pragma once

class IWindow
{
public:
	virtual ~IWindow() {};

	virtual bool Closed() const = 0;
	virtual void ProcessInputs() = 0;
	virtual void Close() = 0;
	virtual HWND GetHandle() const = 0;
	virtual int GetWindowWidth() const = 0;
	virtual int GetWindowHeight() const = 0;
};