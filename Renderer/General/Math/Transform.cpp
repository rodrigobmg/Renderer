#include "stdafx.h"
#include "Transform.h"

Transform::Transform()
	:m_position(0.0f)
	,m_rotation(0.0f)
	,m_scale(1.0f)
{
}

Transform & Transform::operator=(const Transform & other)
{
	m_position = other.m_position;
	m_rotation = other.m_rotation;
	m_scale = other.m_scale;
	return *this;
}

const Matrix4d Transform::GetMatrix()
{
	return MatrixScale(m_scale) * MatrixRotationRollPitchYawDeg(m_rotation.m_x, m_rotation.m_y, m_rotation.m_z) * MatrixTranslation(m_position);
}
