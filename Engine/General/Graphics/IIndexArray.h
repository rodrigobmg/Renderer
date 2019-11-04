#pragma once

class IIndexArray
{
public:
	virtual ~IIndexArray() {};

	virtual size_t GetIndexCount() const = 0;
	virtual const uint32_t* GetIndexData() const = 0;
};