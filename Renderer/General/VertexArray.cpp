#include "VertexArray.h"
#include "VertexElement.h"

VertexArray::VertexArray(size_t vertexCount, const byte* vertexData, const vector<VertexElement>& vertexElements)
	:m_vertexElements(vertexElements)
	,m_vertexCount(vertexCount)
{
	m_bufferSize = 0;
	for (VertexElement& vertexElement : m_vertexElements)
	{
		m_bufferSize += VertexElement::GetVertexElementSize(vertexElement.m_type);
	}
	m_bufferSize *= vertexCount;

	m_vertexData = new byte[m_bufferSize];
	memcpy(m_vertexData, vertexData, m_bufferSize);
}

VertexArray::~VertexArray()
{
	delete[] m_vertexData;
}
