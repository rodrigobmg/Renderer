#include "Math.h"

#ifdef DIRECTX
using namespace DirectX;
#endif

Vector3d Math::Vec3TransformCoord(const Vector3d & vector, const Matrix4d & transformationMatrix)
{
#ifdef DIRECTX
	XMVECTOR array;
	array.m128_f32[0] = vector.x;
	array.m128_f32[1] = vector.y;
	array.m128_f32[2] = vector.z;
	return Vector3d(XMVector3TransformCoord(array, transformationMatrix).m128_f32);
#endif // DIRECTX
}

Matrix4d Math::MatrixRotationRollPitchYawDeg(float roll, float pitch, float yaw)
{
	return MatrixRotationRollPitchYaw(roll * DEG2RAD, pitch * DEG2RAD, yaw * DEG2RAD);
}

Matrix4d Math::MatrixRotationRollPitchYaw(float roll, float pitch, float yaw)
{
#ifdef DIRECTX
	return XMMatrixRotationRollPitchYaw(roll, pitch, yaw);
#endif // DIRECTX
}

Vector3d Math::VectorAdd(const Vector3d & lhs, const Vector3d & rhs)
{
	return Vector3d(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Matrix4d Math::MatrixLookAtLH(const Vector3d & position, const Vector3d & lookAt, const Vector3d & up)
{
#ifdef DIRECTX
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

Matrix4d Math::MatrixTranspose(const Matrix4d & matrix)
{
#ifdef DIRECTX
	return XMMatrixTranspose(matrix);
#endif // DIRECTX

}

Matrix4d Math::MatrixPerspectiveFovLH(float FOV, float aspectRatio, float nearZ, float farZ)
{
#ifdef DIRECTX
	return XMMatrixPerspectiveFovLH(FOV, aspectRatio, nearZ, farZ);
#endif
}

Matrix4d Math::MatrixIdentity()
{
#ifdef DIRECTX
	return XMMatrixIdentity();
#endif
}

Matrix4d Math::MatrixOrthographicLH(float width, float height, float nearZ, float farZ)
{
#ifdef DIRECTX
	return XMMatrixOrthographicLH(width, height, nearZ, farZ);
#endif
}

Matrix4d Math::MatrixTranslation(const Vector3d & translation)
{
#ifdef DIRECTX
	return XMMatrixTranslation(translation.x, translation.y, translation.z);
#endif
}

Matrix4d Math::MatrixScale(const Vector3d & scale)
{
#ifdef DIRECTX
	return XMMatrixScaling(scale.x, scale.y, scale.z);
#endif
}

Matrix4d Math::MatrixMultiply(const Matrix4d & m1, const Matrix4d & m2)
{
#ifdef DIRECTX
	return XMMatrixMultiply(m1, m2);
#endif
}

Matrix4d Math::MatrixInverse(const Matrix4d & matrix)
{
#ifdef DIRECTX
	return XMMatrixInverse(NULL, matrix);
#endif
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
