#include "stdafx.h"
#include "Vector4d.h"

#include "Matrix4d.h"
#include "Vector3d.h"

Vector4d::Vector4d()
	:m_x(0.f)
	,m_y(0.f)
	,m_z(0.f)
	,m_w(0.f)
{
}

Vector4d::Vector4d(float x)
	:m_x(x)
	,m_y(x)
	,m_z(x)
	,m_w(x)
{
}

Vector4d::Vector4d(float x, float y, float z, float w)
	:m_x(x)
	,m_y(y)
	,m_z(z)
	,m_w(w)
{
}

Vector4d::Vector4d(const Vector4d & other)
	:m_vector(other.m_vector)
{
}

Vector4d::Vector4d(const DirectX::XMVECTOR & other)
	:m_vector(other)
{
}

Vector4d::Vector4d(const float * data)
	:m_x(data[0])
	,m_y(data[1])
	,m_z(data[2])
	,m_w(data[3])
{
}

Vector4d & Vector4d::operator=(const Vector4d & other)
{
	m_vector = other.m_vector;
	return *this;
}

Vector4d operator+(const Vector4d & v1, const Vector4d & v2)
{
	return Vector4d(v1.m_x + v2.m_x, v1.m_y + v2.m_y, v1.m_z + v2.m_z, v1.m_w + v2.m_w);
}

Vector4d operator*(const Vector4d & lhs, const Matrix4d & rhs)
{
	return DirectX::XMVector4Transform(lhs, rhs);
}
