#include "stdafx.h"
#include "Transform.h"

Transform::Transform()
	:m_position(0.0f)
	,m_scale(1.0f)
{
}

Transform & Transform::operator=(const Transform & other)
{
	m_position = other.m_position;
	m_orientation = other.m_orientation;
	m_scale = other.m_scale;
	return *this;
}

const Matrix4d Transform::GetMatrix()
{
	return MatrixScale(m_scale) * m_orientation.GetRotationMatrix() * MatrixTranslation(m_position);
}
