#pragma once

class IApplication
{
public:
	virtual ~IApplication() {};
	virtual void Start() = 0;
};