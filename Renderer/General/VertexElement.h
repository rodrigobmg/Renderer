#pragma once

enum class VertexElementType
{
	FLOAT1,
	FLOAT2,
	FLOAT3,
	FLOAT4
};

struct VertexElement
{
public:
	static size_t GetVertexElementSize(VertexElementType type);

	string				m_name;
	VertexElementType	m_type;
	uint16_t			m_offset;
};