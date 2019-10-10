#pragma once

class IConstantBuffer
{
public:
	virtual ~IConstantBuffer() {}

	virtual bool SetData(const void* data) = 0;
};