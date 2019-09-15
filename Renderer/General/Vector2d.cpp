#include "stdafx.h"
#include "Vector2d.h"

Vector2d::Vector2d()
	:x(0.f)
	,y(0.f)
{
}

Vector2d::Vector2d(float x)
	:x(x)
	,y(x)
{
}

Vector2d::Vector2d(float x, float y)
	:x(x)
	,y(y)
{
}

Vector2d::Vector2d(const Vector2d & other)
	:m_vector(other.m_vector)
{
}

Vector2d::Vector2d(const DirectX::XMFLOAT2 & other)
	:m_vector(other)
{
}

Vector2d::Vector2d(const float * data)
	:x(data[0])
	,y(data[1])
{
}

Vector2d & Vector2d::operator=(const Vector2d & other)
{
	m_vector = other.m_vector;
	return *this;
}

Vector2d operator+(const Vector2d & v1, const Vector2d & v2)
{
	return Vector2d(v1.x + v2.x, v1.y + v2.y);
}
