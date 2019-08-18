#pragma once

#include <General/Math/Math.h>

class IConstantBuffer
{
public:
	virtual ~IConstantBuffer() {}

	virtual bool SetData(const void* data) = 0;
};