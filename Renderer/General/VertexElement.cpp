#include "stdafx.h"
#include "VertexElement.h"

VertexElement::VertexElement(const string& name, const byte* data, uint16_t count, VertexElementType type)
	:m_name(name)
	,m_count(count)
	,m_bufferSize(GetVertexElementSize(m_type)* count)
	,m_type(type)
{
	m_data = new byte[m_bufferSize];
	memcpy(m_data, data, m_bufferSize);
}

VertexElement::~VertexElement()
{
	if (m_data)
	{
		delete[] m_data;
	}
}

size_t VertexElement::GetVertexElementSize(VertexElementType type)
{
	switch (type)
	{
	case VertexElementType::FLOAT1:
		return sizeof(float);
		break;
	case VertexElementType::FLOAT2:
		return sizeof(float) * 2;
		break;
	case VertexElementType::FLOAT3:
		return sizeof(float) * 3;
		break;
	case VertexElementType::FLOAT4:
		return sizeof(float) * 4;
		break;
	default:
		assert(false);
		break;
	}
	return 0;
}
