#pragma once
#include "Matrix4d.h"
#include "Vector3d.h"

class Quaternion
{
public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	explicit Quaternion(const Vector3d& eulerAngles);
	Quaternion(const Quaternion& other);
	Quaternion(const Vector3d& axis, float rotationAngle);
	Quaternion(const DirectX::XMVECTOR& quaternion) { m_quaternion = quaternion; }
	Matrix4d GetRotationMatrix() const;
	Quaternion& operator=(const Quaternion& other);
	Quaternion& operator*=(const Quaternion& other);
	Quaternion GetInverse() const;
	~Quaternion() {}

	operator DirectX::XMVECTOR() const { return m_quaternion; }

private:
	union
	{
		DirectX::XMVECTOR m_quaternion;
		struct
		{
			float x, y, z, w;
		};
	};
};

Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);