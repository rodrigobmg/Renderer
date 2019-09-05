#include "stdafx.h"
#include "Matrix4d.h"

#include "Vector3d.h"

Matrix4d::Matrix4d()
	:m_00(0.0f), m_01(0.0f), m_02(0.0f), m_03(0.0f)
	,m_10(0.0f), m_11(0.0f), m_12(0.0f), m_13(0.0f)
	,m_20(0.0f), m_21(0.0f), m_22(0.0f), m_23(0.0f)
	,m_30(0.0f), m_31(0.0f), m_32(0.0f), m_33(0.0f)
{
}

Matrix4d::Matrix4d(const Matrix4d & other)
	:m_matrix(other.m_matrix)
{
}

Matrix4d::Matrix4d(const DirectX::XMMATRIX & other)
	:m_matrix(other)
{
}

Matrix4d & Matrix4d::operator=(const Matrix4d & other)
{
	m_matrix = other.m_matrix;
	return *this;
}

Matrix4d operator*(const Matrix4d & m1, const Matrix4d & m2)
{
	return DirectX::XMMatrixMultiply(m1, m2);
}

Matrix4d MatrixRotationRollPitchYawDeg(float roll, float pitch, float yaw)
{
	return MatrixRotationRollPitchYaw(roll * Math::DEG2RAD, pitch * Math::DEG2RAD, yaw * Math::DEG2RAD);
}

Matrix4d MatrixRotationRollPitchYaw(float roll, float pitch, float yaw)
{
	return DirectX::XMMatrixRotationRollPitchYaw(roll, pitch, yaw);
}

Matrix4d MatrixLookAtLH(const Vector3d & position, const Vector3d & lookAt, const Vector3d & up)
{
	return DirectX::XMMatrixLookAtLH(position, lookAt, up);
}

Matrix4d MatrixTranspose(const Matrix4d & matrix)
{
	return DirectX::XMMatrixTranspose(matrix);
}

Matrix4d MatrixPerspectiveFovLH(float FOV, float aspectRatio, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveFovLH(FOV, aspectRatio, nearZ, farZ);
}

Matrix4d MatrixIdentity()
{
	return DirectX::XMMatrixIdentity();
}

Matrix4d MatrixOrthographicLH(float width, float height, float nearZ, float farZ)
{
	return DirectX::XMMatrixOrthographicLH(width, height, nearZ, farZ);
}

Matrix4d MatrixTranslation(const Vector3d & translation)
{
	return DirectX::XMMatrixTranslation(translation.m_x, translation.m_y, translation.m_z);
}

Matrix4d MatrixScale(const Vector3d & scale)
{
	return DirectX::XMMatrixScaling(scale.m_x, scale.m_y, scale.m_z);
}

Matrix4d MatrixInverse(const Matrix4d & matrix)
{
	return DirectX::XMMatrixInverse(NULL, matrix);
}
