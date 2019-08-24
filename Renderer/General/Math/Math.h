#pragma once

#ifdef DIRECTX
#include <DirectXMath.h>
typedef DirectX::XMMATRIX Matrix4d;
typedef DirectX::XMFLOAT4 Vector4d;
typedef DirectX::XMFLOAT3 Vector3d;
typedef DirectX::XMFLOAT2 Vector2d;
#endif

namespace Math
{
	static const float DEG2RAD = 0.0174532925f;
	static const float RAD2DEG = 1.0f / DEG2RAD;
	static constexpr float PI = 22.0f / 7.0f;

	Vector3d Vec3TransformCoord(const Vector3d& vector, const Matrix4d& transformationMatrix);
	Matrix4d MatrixRotationRollPitchYawDeg(float roll, float pitch, float yaw);
	Matrix4d MatrixRotationRollPitchYaw(float roll, float pitch, float yaw);
	Vector3d VectorAdd(const Vector3d& lhs, const Vector3d& rhs);
	Matrix4d MatrixLookAtLH(const Vector3d& position, const Vector3d& lookAt, const Vector3d& up);
	Matrix4d MatrixTranspose(const Matrix4d& matrix);
	Matrix4d MatrixPerspectiveFovLH(float FOV, float aspectRatio, float nearZ, float farZ);
	Matrix4d MatrixIdentity();
	Matrix4d MatrixOrthographicLH(float width, float height, float nearZ, float farZ);
	Matrix4d MatrixTranslation(const Vector3d& translation);
	Matrix4d MatrixScale(const Vector3d& scale);
	Matrix4d MatrixMultiply(const Matrix4d& m1, const Matrix4d& m2);
	Matrix4d MatrixInverse(const Matrix4d& matrix);
}

class Transform
{
public:
	Transform();
	~Transform() {}

	const Matrix4d GetMatrix();

	Vector3d	m_position;
	Vector3d	m_rotation;
	Vector3d	m_scale;
};

class Color
{
public:
	Color();
	Color(float r);
	Color(float r, float g, float b, float a);
	Color(const Color& other);
	~Color() {}

	Vector4d ToVec4() const;

	float	m_r;
	float	m_g;
	float	m_b;
	float	m_a;
};