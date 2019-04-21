#pragma once

class Matrix3d
{
public:
	Matrix3d();
	~Matrix3d() {};
private:
	float m_00, m_01, m_02,
		m_10, m_11, m_12,
		m_20, m_21, m_22;
};