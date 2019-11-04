#pragma once
#include "IIndexArray.h"

class IndexArray : public IIndexArray
{
public:
	IndexArray(size_t indexCount, const uint32_t* indexData);
	~IndexArray();

	virtual size_t GetIndexCount() const override { return m_indexCount; }
	virtual const uint32_t* GetIndexData() const override { return m_indexData; }

private:
	uint32_t*	m_indexData;
	size_t		m_indexCount;
};