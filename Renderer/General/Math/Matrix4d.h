#pragma once

class Vector3d;
class Matrix4d
{
public:
	Matrix4d();
	Matrix4d(const Matrix4d& other);
	Matrix4d(const DirectX::XMMATRIX& other);
	Matrix4d& operator=(const Matrix4d& other);
	~Matrix4d() {}

	operator DirectX::XMMATRIX() const { return m_matrix; }

private:
	union
	{
		DirectX::XMMATRIX m_matrix;
		struct
		{
			float
				m_00, m_01, m_02, m_03,
				m_10, m_11, m_12, m_13,
				m_20, m_21, m_22, m_23,
				m_30, m_31, m_32, m_33;
		};
	};
};

Matrix4d operator*(const Matrix4d& m1, const Matrix4d& m2);
Matrix4d MatrixRotationRollPitchYawDeg(float roll, float pitch, float yaw);
Matrix4d MatrixRotationRollPitchYaw(float roll, float pitch, float yaw);
Matrix4d MatrixLookAtLH(const Vector3d& position, const Vector3d& lookAt, const Vector3d& up);
Matrix4d MatrixTranspose(const Matrix4d& matrix);
Matrix4d MatrixPerspectiveFovLH(float FOV, float aspectRatio, float nearZ, float farZ);
Matrix4d MatrixIdentity();
Matrix4d MatrixOrthographicLH(float width, float height, float nearZ, float farZ);
Matrix4d MatrixTranslation(const Vector3d& translation);
Matrix4d MatrixScale(const Vector3d& scale);
Matrix4d MatrixInverse(const Matrix4d& matrix);
