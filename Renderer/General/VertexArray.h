#pragma once
#include "IVertexArray.h"

struct VertexElement;
class VertexArray : public IVertexArray
{
public:
	VertexArray(size_t vertexCount, const byte* vertexData, const vector<VertexElement>& vertexElements);
	~VertexArray();

	virtual size_t GetVertexCount() const override { return m_vertexCount; }
	virtual const byte* GetVertexData() const override { return m_vertexData; }
	virtual size_t GetBufferSize() const override { return m_bufferSize; }
	virtual size_t GetStride() const override { return m_bufferSize / m_vertexCount; }

private:
	vector<VertexElement>	m_vertexElements;
	byte*					m_vertexData;
	size_t					m_vertexCount;
	size_t					m_bufferSize;
};