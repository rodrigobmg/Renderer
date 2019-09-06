#pragma once

enum class VertexElementType
{
	FLOAT1,
	FLOAT2,
	FLOAT3,
	FLOAT4
};

class VertexElement
{
public:
	VertexElement(const string& name, const byte* data, uint16_t count, VertexElementType type);
	VertexElement(const VertexElement&) = delete;
	VertexElement& operator=(const VertexElement&) = delete;
	~VertexElement();

	static size_t GetVertexElementSize(VertexElementType type);

private:
	string				m_name;
	byte*				m_data;
	uint16_t			m_count;
	size_t				m_bufferSize;
	VertexElementType	m_type;
};