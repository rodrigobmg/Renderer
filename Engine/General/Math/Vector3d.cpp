#include "pch.h"
#include "Vector3d.h"

#include "Vector4d.h"
#include "Quaternion.h"

const Vector3d Vector3d::kUp(0.0f, 1.0f, 0.0f);
const Vector3d Vector3d::kForward(0.0f, 0.0f, 1.0f);
const Vector3d Vector3d::kSide(1.0f, 0.0f, 0.0f);

Vector3d::Vector3d()
	: x(0.f)
	, y(0.f)
	, z(0.f)
{
}

Vector3d::Vector3d(float x)
	: x(x)
	, y(x)
	, z(x)
{
}

Vector3d::Vector3d(float x, float y, float z)
	: x(x)
	, y(y)
	, z(z)
{
}

Vector3d::Vector3d(const Vector3d & other)
	: m_vector(other.m_vector)
{
}

Vector3d::Vector3d(const DirectX::XMFLOAT3 & other)
	: m_vector(other)
{
}

Vector3d::Vector3d(const DirectX::XMVECTOR& other)
	: x(other.m128_f32[0])
	, y(other.m128_f32[1])
	, z(other.m128_f32[2])
{
}

Vector3d::Vector3d(const Vector4d & other)
	:x(other.x)
	,y(other.y)
	,z(other.z)
{
}

Vector3d & Vector3d::operator=(const Vector3d & rhs)
{
	m_vector = rhs.m_vector;
	return *this;
}

Vector3d& Vector3d::operator+=(const Vector3d& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3d& Vector3d::operator-=(const Vector3d& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
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
	:x(data[0])
	,y(data[1])
	,z(data[2])
{
}

Vector3d::operator DirectX::XMVECTOR() const
{
	DirectX::XMVECTOR vector;
	vector.m128_f32[0] = x;
	vector.m128_f32[1] = y;
	vector.m128_f32[2] = z;
	return vector;
}

float Vector3d::GetSquaredLength() const
{
	return Dot(*this, *this);
}

float Vector3d::GetLength() const
{
	return sqrtf(GetSquaredLength());
}

Vector3d operator+(const Vector3d & v1, const Vector3d & v2)
{
	return Vector3d(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3d operator*(const Vector3d& lhs, float rhs)
{
	return Vector3d(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

Vector3d operator/(const Vector3d& lhs, float rhs)
{
	return lhs * (1.0f / rhs);
}

float Dot(const Vector3d& a, const Vector3d& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3d Normalize(const Vector3d& vector)
{
	float length = vector.GetLength();
	return vector / length;
}

Vector3d operator*(const Vector3d& lhs, const Quaternion& rhs)
{
	return DirectX::XMVector3Rotate(lhs, rhs);
}
