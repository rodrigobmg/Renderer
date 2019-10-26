#pragma once

class IApplication
{
public:
	virtual ~IApplication() {};

	virtual void Run() = 0;
	virtual bool IsReady() const = 0;
};