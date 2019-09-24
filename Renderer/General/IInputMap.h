#pragma once

class IInputMap
{
public:
	virtual ~IInputMap() {}

	virtual unsigned int GetMappedValue(unsigned int key) const = 0;
};