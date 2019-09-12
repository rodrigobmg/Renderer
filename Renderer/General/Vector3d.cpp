#include "stdafx.h"
#include "Vector3d.h"

#include "Vector4d.h"

Vector3d::Vector3d()
	:m_x(0.f)
	,m_y(0.f)
	,m_z(0.f)
{
}

Vector3d::Vector3d(float x)
	:m_x(x)
	,m_y(x)
	,m_z(x)
{
}

Vector3d::Vector3d(float x, float y, float z)
	:m_x(x)
	,m_y(y)
	,m_z(z)
{
}

Vector3d::Vector3d(const Vector3d & other)
	:m_vector(other.m_vector)
{
}

Vector3d::Vector3d(const DirectX::XMFLOAT3 & other)
	:m_vector(other)
{
}

Vector3d::Vector3d(const Vector4d & other)
	:m_x(other.m_x)
	,m_y(other.m_y)
	,m_z(other.m_z)
{
}

Vector3d & Vector3d::operator=(const Vector3d & other)
{
	m_vector = other.m_vector;
	return *this;
}

Vector3d& Vector3d::operator*=(float rhs)
{
	m_vector.x *= rhs;
	m_vector.y *= rhs;
	m_vector.z *= rhs;
	return *this;
}

Vector3d::Vector3d(const float * data)
	:m_x(data[0])
	,m_y(data[1])
	,m_z(data[2])
{
}

Vector3d::operator DirectX::XMVECTOR() const
{
	DirectX::XMVECTOR vector;
	vector.m128_f32[0] = m_x;
	vector.m128_f32[1] = m_y;
	vector.m128_f32[2] = m_z;
	return vector;
}

Vector3d operator+(const Vector3d & v1, const Vector3d & v2)
{
	return Vector3d(v1.m_x + v2.m_x, v1.m_y + v2.m_y, v1.m_z + v2.m_z);
}