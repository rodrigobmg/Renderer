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
	VertexElement()
		: m_type(VertexElementType::FLOAT1)
		, m_offset(0)
		, m_index(0)
	{}

	static uint16_t GetVertexElementSize(VertexElementType type);

	string				m_name;
	VertexElementType	m_type;
	uint16_t			m_offset;
	uint8_t				m_index;
};