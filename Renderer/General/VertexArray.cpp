#include "VertexArray.h"

VertexArray::VertexArray(size_t vertexCount, const VertexFormat * vertexData)
	:m_vertexCount(vertexCount)
{
	m_vertexData = new VertexFormat[vertexCount];
	memcpy(m_vertexData, vertexData, sizeof(VertexFormat) * vertexCount);
}

VertexArray::~VertexArray()
{
	delete[] m_vertexData;
}
