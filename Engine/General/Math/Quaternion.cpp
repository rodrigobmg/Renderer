#include "pch.h"
#include "Quaternion.h"

#include "Vector3d.h"

Quaternion::Quaternion()
	: x(0.f)
	, y(0.f)
	, z(0.f)
	, w(1.f)
{
}

Quaternion::Quaternion(float x, float y, float z, float w)
	: x(x)
	, y(y)
	, z(z)
	, w(w)
{
}

Quaternion::Quaternion(const Vector3d& eulerAngles)
	: m_quaternion(DirectX::XMQuaternionRotationRollPitchYaw(eulerAngles.x, eulerAngles.y, eulerAngles.z))
{
}

Quaternion::Quaternion(const Quaternion& other)
	: m_quaternion(other.m_quaternion)
{
}

Quaternion::Quaternion(const Vector3d& axis, float rotationAngle)
{
	Vector3d rotationAxis = Normalize(axis);
	x = rotationAxis.x * sin(rotationAngle * 0.5f);
	y = rotationAxis.y * sin(rotationAngle * 0.5f);
	z = rotationAxis.z * sin(rotationAngle * 0.5f);
	w = cos(rotationAngle * 0.5f);
}

Matrix4d Quaternion::GetRotationMatrix() const
{
	return DirectX::XMMatrixRotationQuaternion(m_quaternion);
}

Quaternion& Quaternion::operator=(const Quaternion& other)
{
	m_quaternion = other.m_quaternion;
	return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& other)
{
	m_quaternion = DirectX::XMQuaternionMultiply(m_quaternion, other.m_quaternion);
	return *this;
}

Quaternion Quaternion::GetInverse() const
{
	return DirectX::XMQuaternionInverse(m_quaternion);
}

Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion local = lhs;
	local *= rhs;
	return local;
}