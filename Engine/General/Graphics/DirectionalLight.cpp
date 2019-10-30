#include "pch.h"
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
	: Light()
	, m_direction(0.0f, 0.0f, -1.0f)
{
}

DirectionalLight::DirectionalLight(const DirectionalLight& other)
	: Light(other)
	, m_direction(other.m_direction)
{
}
