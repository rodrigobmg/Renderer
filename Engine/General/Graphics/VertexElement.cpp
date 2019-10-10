#include "pch.h"
#include "VertexElement.h"

uint16_t VertexElement::GetVertexElementSize(VertexElementType type)
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
