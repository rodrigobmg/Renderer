#include "pch.h"
#include "Transform.h"

Transform::Transform()
	: m_position(0.0f)
	, m_scale(1.0f)
{
}

Transform & Transform::operator=(const Transform & other)
{
	m_position = other.m_position;
	m_orientation = other.m_orientation;
	m_scale = other.m_scale;
	return *this;
}

void Transform::Set(const Matrix4d& matrix)
{
	bool result = matrix.Decompose(m_position, m_scale, m_orientation);
	assert(result);
}

const Matrix4d Transform::GetMatrix() const
{
	return Math::MatrixScale(m_scale) * m_orientation.GetRotationMatrix() * Math::MatrixTranslation(m_position);
}
