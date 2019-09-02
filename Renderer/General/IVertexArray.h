#pragma once
#include <General/Math/Vector2d.h>
#include <General/Math/Vector3d.h>
#include <General/Math/Vector4d.h>

struct VertexFormat
{
	Vector3d	m_position;
	Vector4d	m_color;
	Vector3d	m_normal;
	Vector2d	m_texcoord0;
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
