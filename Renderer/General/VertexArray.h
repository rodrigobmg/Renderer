#pragma once
#include "IVertexArray.h"

class VertexArray : public IVertexArray
{
public:
	VertexArray(size_t vertexCount, const VertexFormat* vertexData);
	~VertexArray();

	virtual size_t GetVertexCount() const override { return m_vertexCount; }
	virtual const VertexFormat* GetVertexData() const override { return m_vertexData; }

private:
	VertexFormat*	m_vertexData;
	size_t			m_vertexCount;
};