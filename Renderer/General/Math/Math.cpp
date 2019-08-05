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

Matrix4d Math::MatrixRotationRollPitchYaw(float roll, float pitch, float yaw)
{
#ifdef DIRECTX
	return XMMatrixRotationRollPitchYaw(roll, pitch, yaw);
#endif // DIRECTX
}

Vector3d Math::VectorAdd(const Vector3d & lhs, const Vector3d & rhs)
{
#ifdef DIRECTX
	return Vector3d(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
#endif // DIRECTX
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
