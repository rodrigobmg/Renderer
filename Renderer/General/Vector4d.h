#pragma once

class Vector3d;
class Vector4d
{
public:
	Vector4d();
	Vector4d(float x);
	Vector4d(float x, float y, float z, float w);
	Vector4d(const Vector4d& other);
	Vector4d(const Vector3d& other, float w = 0);
	Vector4d(const DirectX::XMVECTOR& other);
	Vector4d(const float* data);
	Vector4d& operator=(const Vector4d& other);
	Vector4d& operator=(const Vector3d& other);
	~Vector4d() {}

	operator DirectX::XMVECTOR() const { return m_vector; }

	union
	{
		DirectX::XMVECTOR m_vector;
		struct
		{
			float x, y, z, w;
		};
	};
};

class Matrix4d;
Vector4d operator+(const Vector4d& v1, const Vector4d& v2);
Vector4d operator*(const Vector4d& lhs, const Matrix4d& rhs);