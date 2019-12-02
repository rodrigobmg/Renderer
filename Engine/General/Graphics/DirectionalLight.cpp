#include "pch.h"
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const Color& color, const Quaternion& orientation)
	: Light(LightType::kDirectional, color)
	, m_orientation(orientation)
{
}

DirectionalLight::DirectionalLight(const DirectionalLight& other)
	: Light(other)
	, m_orientation(other.m_orientation)
{
}
