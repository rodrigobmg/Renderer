#include "pch.h"
#include "Light.h"

#include "Material.h"
#include "IGraphics.h"
#include "Loader.h"

#include "Scene.h"
#include "SceneNode.h"
#include "MeshNode.h"

Light::Light(LightType type, const Color& color, float intensity)
	: m_color(color)
	, m_intensity(intensity)
	, m_type(type)
{
}

Light::Light(const Light& other)
	: m_color(other.m_color)
	, m_intensity(other.m_intensity)
	, m_type(other.m_type)
{
}
