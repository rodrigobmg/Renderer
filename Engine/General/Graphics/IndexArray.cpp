#include "pch.h"
#include "IndexArray.h"

IndexArray::IndexArray(size_t indexCount, const uint32_t* indexData)
	:m_indexCount(indexCount)
{
	m_indexData = new uint32_t[indexCount];
	memcpy(m_indexData, indexData, sizeof(uint32_t) * indexCount);
}

IndexArray::~IndexArray()
{
	delete[] m_indexData;
}
