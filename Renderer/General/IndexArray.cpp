#include "IndexArray.h"
#include <memory>

IndexArray::IndexArray(size_t indexCount, const uint16_t* indexData)
	:m_indexCount(indexCount)
{
	m_indexData = new uint16_t[indexCount];
	memcpy(m_indexData, indexData, sizeof(uint16_t) * indexCount);
}

IndexArray::~IndexArray()
{
	delete[] m_indexData;
}
