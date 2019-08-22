#pragma once
#include <General/Math/Math.h>

struct VertexFormat
{
	Vector3d	m_position;
	Vector4d	m_color;
	Vector3d	m_normal;
};

enum class PrimitiveType
{
	Points = 0,
	Line,
	LineStrip,
	Triangles,
	TriangleStrip
};

class IVertexArray
{
public:
	virtual ~IVertexArray() {};
	virtual size_t GetVertexCount() const = 0;
	virtual const VertexFormat* GetVertexData() const = 0;
};