#include "pch.h"
#include "PointLight.h"

PointLight::PointLight(const Color& color, const Vector3d& position)
	: Light(LightType::kPoint, color)
	, m_position(position)
{
}

PointLight::PointLight(const PointLight& other)
	: Light(other)
	, m_position(other.m_position)
{
}