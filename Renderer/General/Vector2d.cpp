#include "stdafx.h"
#include "Vector2d.h"

Vector2d::Vector2d()
	:m_x(0.f)
	,m_y(0.f)
{
}

Vector2d::Vector2d(float x)
	:m_x(x)
	,m_y(x)
{
}

Vector2d::Vector2d(float x, float y)
	:m_x(x)
	,m_y(y)
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
	:m_x(data[0])
	,m_y(data[1])
{
}

Vector2d & Vector2d::operator=(const Vector2d & other)
{
	m_vector = other.m_vector;
	return *this;
}

Vector2d operator+(const Vector2d & v1, const Vector2d & v2)
{
	return Vector2d(v1.m_x + v2.m_x, v1.m_y + v2.m_y);
}
