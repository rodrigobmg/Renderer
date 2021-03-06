#include "pch.h"
#include "Matrix4d.h"

#include "Vector3d.h"
#include "Quaternion.h"

const Matrix4d Matrix4d::kIdentity(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
);

Matrix4d::Matrix4d()
	:m_00(0.0f), m_01(0.0f), m_02(0.0f), m_03(0.0f)
	,m_10(0.0f), m_11(0.0f), m_12(0.0f), m_13(0.0f)
	,m_20(0.0f), m_21(0.0f), m_22(0.0f), m_23(0.0f)
	,m_30(0.0f), m_31(0.0f), m_32(0.0f), m_33(0.0f)
{
}

Matrix4d::Matrix4d(
	float a00, float a01, float a02, float a03,
	float a10, float a11, float a12, float a13,
	float a20, float a21, float a22, float a23,
	float a30, float a31, float a32, float a33
)
	: m_00(a00), m_01(a01), m_02(a02), m_03(a03)
	, m_10(a10), m_11(a11), m_12(a12), m_13(a13)
	, m_20(a20), m_21(a21), m_22(a22), m_23(a23)
	, m_30(a30), m_31(a31), m_32(a32), m_33(a33)
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

bool Matrix4d::Decompose(Vector3d& position, Vector3d& scale, Quaternion& orientation) const
{
	DirectX::XMVECTOR outScale, outRot, outPos;
	bool result = DirectX::XMMatrixDecompose(&outScale, &outRot, &outPos, *this);
	position = outPos;
	scale = outScale;
	orientation = outRot;
	return result;
}

const Matrix4d& Matrix4d::Identity()
{
	return kIdentity;
}

Matrix4d operator*(const Matrix4d & m1, const Matrix4d & m2)
{
	return DirectX::XMMatrixMultiply(m1, m2);
}

Matrix4d Math::MatrixLookAtLH(const Vector3d & position, const Vector3d & lookAt, const Vector3d & up)
{
	return DirectX::XMMatrixLookAtLH(position, lookAt, up);
}

Matrix4d Math::MatrixTranspose(const Matrix4d & matrix)
{
	return DirectX::XMMatrixTranspose(matrix);
}

Matrix4d Math::MatrixPerspectiveFovLH(float FOV, float aspectRatio, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveFovLH(FOV, aspectRatio, nearZ, farZ);
}

Matrix4d Math::MatrixIdentity()
{
	return DirectX::XMMatrixIdentity();
}

Matrix4d Math::MatrixOrthographicLH(float width, float height, float nearZ, float farZ)
{
	return DirectX::XMMatrixOrthographicLH(width, height, nearZ, farZ);
}

Matrix4d Math::MatrixTranslation(const Vector3d & translation)
{
	return DirectX::XMMatrixTranslation(translation.x, translation.y, translation.z);
}

Matrix4d Math::MatrixScale(const Vector3d & scale)
{
	return DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
}

Matrix4d Math::MatrixInverse(const Matrix4d & matrix)
{
	return DirectX::XMMatrixInverse(NULL, matrix);
}
