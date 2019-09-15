#pragma once

class Vector4d;
class Vector3d
{
public:
	Vector3d();
	Vector3d(float x);
	Vector3d(float x, float y, float z);
	Vector3d(const Vector3d& other);
	Vector3d(const DirectX::XMFLOAT3& other);
	Vector3d(const Vector4d& other);
	Vector3d& operator=(const Vector3d& other);
	Vector3d& operator*=(float rhs);
	Vector3d(const float* data);
	~Vector3d() {}

	operator DirectX::XMFLOAT3() const { return m_vector; }
	operator DirectX::XMVECTOR() const;

	union
	{
		DirectX::XMFLOAT3 m_vector;
		struct
		{
			float x, y, z;
		};
	};
};

class Matrix4d;
Vector3d operator+(const Vector3d& v1, const Vector3d& v2);
Vector3d operator*(const Vector3d& lhs, float rhs);