#include "pch.h"
#include "PointLight.h"

PointLight::PointLight(const Color& color, const Vector3d& position)
	: Light(LightType::kPoint, color)
	, m_position(position)
	, m_worldPosition(position)
{
}

PointLight::PointLight(const PointLight& other)
	: Light(other)
	, m_rotationAroundOrigin(other.m_rotationAroundOrigin)
	, m_position(other.m_position)
	, m_worldPosition(other.m_worldPosition)
{
}

void PointLight::SetPosition(const Vector3d& position)
{
	m_position = position;
	m_worldPosition = m_position;
	m_rotationAroundOrigin = Quaternion();
}

void PointLight::SetRotationAroundOrigin(const Quaternion& rotation)
{
	m_rotationAroundOrigin = rotation;
	m_worldPosition = m_position * m_rotationAroundOrigin;
}
