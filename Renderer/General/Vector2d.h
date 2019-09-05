#pragma once

class Vector2d
{
public:
	Vector2d();
	Vector2d(float x);
	Vector2d(float x, float y);
	Vector2d(const Vector2d& other);
	Vector2d(const DirectX::XMFLOAT2& other);
	Vector2d(const float* data);
	Vector2d& operator=(const Vector2d& other);
	~Vector2d() {}

	operator DirectX::XMFLOAT2() const { return m_vector; }

	union
	{
		DirectX::XMFLOAT2 m_vector;
		struct
		{
			float m_x, m_y;
		};
	};
};

Vector2d operator+(const Vector2d& v1, const Vector2d& v2);