#pragma once

#ifdef DIRECTX
#include <DirectXMath.h>
typedef DirectX::XMMATRIX Matrix4d;
typedef DirectX::XMFLOAT4 Vector4d;
typedef DirectX::XMFLOAT3 Vector3d;
typedef DirectX::XMFLOAT2 Vector2d;
#endif

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