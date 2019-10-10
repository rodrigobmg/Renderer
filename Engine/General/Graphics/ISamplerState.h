#pragma once

class ISamplerState
{
public:
	virtual ~ISamplerState() {}

	virtual bool Initialize() = 0;
	virtual void Bind() = 0;
};