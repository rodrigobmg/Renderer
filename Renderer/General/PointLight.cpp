#include "stdafx.h"
#include "PointLight.h"

PointLight::PointLight()
	: m_color(1.0f)
	, m_position(0.0f, 0.0f, 0.0f)
{
}

PointLight::PointLight(const Color & color, const Vector3d & position)
	: m_color(color)
	, m_position(position.x, position.y, position.z)
{
}