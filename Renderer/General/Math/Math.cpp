#include "Math.h"

#ifdef DIRECTX11
using namespace DirectX;
#endif

namespace Math
{
	Vector3d Vec3TransformCoord(const Vector3d & vector, const Matrix4d & transformationMatrix)
	{
#ifdef DIRECTX11
		XMVECTOR array;
		array.m128_f32[0] = vector.x;
		array.m128_f32[1] = vector.y;
		array.m128_f32[2] = vector.z;
		return Vector3d(XMVector3TransformCoord(array, transformationMatrix).m128_f32);
#endif // DIRECTX
	}

	Matrix4d MatrixRotationRollPitchYawDeg(float roll, float pitch, float yaw)
	{
		return MatrixRotationRollPitchYaw(roll * DEG2RAD, pitch * DEG2RAD, yaw * DEG2RAD);
	}

	Matrix4d MatrixRotationRollPitchYaw(float roll, float pitch, float yaw)
	{
#ifdef DIRECTX11
		return XMMatrixRotationRollPitchYaw(roll, pitch, yaw);
#endif // DIRECTX
	}

	Vector3d VectorAdd(const Vector3d & lhs, const Vector3d & rhs)
	{
		return Vector3d(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	Matrix4d MatrixLookAtLH(const Vector3d & position, const Vector3d & lookAt, const Vector3d & up)
	{
#ifdef DIRECTX11
		XMVECTOR vPosition;
		vPosition.m128_f32[0] = position.x;
		vPosition.m128_f32[1] = position.y;
		vPosition.m128_f32[2] = position.z;

		XMVECTOR vLookAt;
		vLookAt.m128_f32[0] = lookAt.x;
		vLookAt.m128_f32[1] = lookAt.y;
		vLookAt.m128_f32[2] = lookAt.z;

		XMVECTOR vUp;
		vUp.m128_f32[0] = up.x;
		vUp.m128_f32[1] = up.y;
		vUp.m128_f32[2] = up.z;
		return XMMatrixLookAtLH(vPosition, vLookAt, vUp);
#endif // DIRECTX
	}

	Matrix4d MatrixTranspose(const Matrix4d & matrix)
	{
#ifdef DIRECTX11
		return XMMatrixTranspose(matrix);
#endif // DIRECTX

	}

	Matrix4d MatrixPerspectiveFovLH(float FOV, float aspectRatio, float nearZ, float farZ)
	{
#ifdef DIRECTX11
		return XMMatrixPerspectiveFovLH(FOV, aspectRatio, nearZ, farZ);
#endif
	}

	Matrix4d MatrixIdentity()
	{
#ifdef DIRECTX11
		return XMMatrixIdentity();
#endif
	}

	Matrix4d MatrixOrthographicLH(float width, float height, float nearZ, float farZ)
	{
#ifdef DIRECTX11
		return XMMatrixOrthographicLH(width, height, nearZ, farZ);
#endif
	}

	Matrix4d MatrixTranslation(const Vector3d & translation)
	{
#ifdef DIRECTX11
		return XMMatrixTranslation(translation.x, translation.y, translation.z);
#endif
	}

	Matrix4d MatrixScale(const Vector3d & scale)
	{
#ifdef DIRECTX11
		return XMMatrixScaling(scale.x, scale.y, scale.z);
#endif
	}

	Matrix4d MatrixMultiply(const Matrix4d & m1, const Matrix4d & m2)
	{
#ifdef DIRECTX11
		return XMMatrixMultiply(m1, m2);
#endif
	}

	Matrix4d MatrixInverse(const Matrix4d & matrix)
	{
#ifdef DIRECTX11
		return XMMatrixInverse(NULL, matrix);
#endif
	}
}

Transform::Transform()
	:m_position(0.0f, 0.0f, 0.0f)
	,m_rotation(0.0f, 0.0f, 0.0f)
	,m_scale(1.0f, 1.0f, 1.0f)
{
}

const Matrix4d Transform::GetMatrix()
{
	using namespace Math;
	return MatrixMultiply(MatrixScale(m_scale), MatrixMultiply(MatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z), MatrixTranslation(m_position)));
}

Color::Color()
	: m_r(0.0f)
	, m_g(0.0f)
	, m_b(0.0f)
	, m_a(1.0f)
{
}

Color::Color(float r)
	: m_r(r)
	, m_g(r)
	, m_b(r)
	, m_a(1.0f)
{
}

Color::Color(float r, float g, float b, float a)
	: m_r(r)
	, m_g(g)
	, m_b(b)
	, m_a(a)
{
}

Color::Color(const Color & other)
	: m_r(other.m_r)
	, m_g(other.m_g)
	, m_b(other.m_b)
	, m_a(other.m_a)
{
}

Vector4d Color::ToVec4() const
{
	return Vector4d(m_r, m_g, m_b, m_a);
}
