#pragma once
#include <stdint.h>

class IIndexArray
{
public:
	virtual ~IIndexArray() {};

	virtual size_t GetIndexCount() const = 0;
	virtual const uint16_t* GetIndexData() const = 0;
};