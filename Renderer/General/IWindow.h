#pragma once

class IWindow
{
public:
	virtual ~IWindow() {};
	virtual bool Closed() const = 0;
	virtual void ProcessInputs() = 0;
	virtual void SwapBuffers() = 0;
	virtual void Close() = 0;
};