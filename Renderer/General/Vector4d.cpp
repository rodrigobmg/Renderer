#include "stdafx.h"
#include "Vector4d.h"

#include "Matrix4d.h"
#include "Vector3d.h"

Vector4d::Vector4d()
	:x(0.f)
	,y(0.f)
	,z(0.f)
	,w(0.f)
{
}

Vector4d::Vector4d(float x)
	:x(x)
	,y(x)
	,z(x)
	,w(x)
{
}

Vector4d::Vector4d(float x, float y, float z, float w)
	: x(x)
	, y(y)
	, z(z)
	, w(w)
{
}

Vector4d::Vector4d(const Vector4d & other)
	:m_vector(other.m_vector)
{
}

Vector4d::Vector4d(const Vector3d& other, float w)
	: x(other.x)
	, y(other.y)
	, z(other.z)
	, w(w)
{
}

Vector4d::Vector4d(const DirectX::XMVECTOR & other)
	:m_vector(other)
{
}

Vector4d::Vector4d(const float * data)
	:x(data[0])
	,y(data[1])
	,z(data[2])
	,w(data[3])
{
}

Vector4d & Vector4d::operator=(const Vector4d & other)
{
	m_vector = other.m_vector;
	return *this;
}

Vector4d& Vector4d::operator=(const Vector3d& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = 1.0;
	return *this;
}

Vector4d operator+(const Vector4d & v1, const Vector4d & v2)
{
	return Vector4d(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

Vector4d operator*(const Vector4d & lhs, const Matrix4d & rhs)
{
	return DirectX::XMVector4Transform(lhs, rhs);
}
