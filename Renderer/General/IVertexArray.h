#pragma once

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
	virtual const byte* GetVertexData() const = 0;
	virtual size_t GetBufferSize() const = 0;
	virtual size_t GetStride() const = 0;
};
