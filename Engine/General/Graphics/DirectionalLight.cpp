#include "pch.h"
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
	: Light(LightType::kDirectional)
	, m_direction(0.f, 0.f, -1.0f)
{
}

DirectionalLight::DirectionalLight(const Color& color, const Vector3d& direction, const IGraphicsPtr& graphics)
	: Light(color, graphics, LightType::kDirectional)
	, m_direction(direction)
{
}

DirectionalLight::DirectionalLight(const DirectionalLight& other)
	: Light(other)
	, m_direction(other.m_direction)
{
}
