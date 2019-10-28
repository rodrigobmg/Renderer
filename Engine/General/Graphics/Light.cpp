#include "pch.h"
#include "Light.h"

#include "SceneObject.h"
#include "Loader.h"

Light::Light(LightType lightType)
	: m_color(1.0f)
	, m_lightType(lightType)
{
}

Light::Light(const Color& color, const IGraphicsPtr& graphics, LightType lightType)
	: m_color(color)
	, m_lightType(lightType)
{
	m_sceneObject = Loader::LoadModel("Assets/pointlight.object", graphics);
}

Light::Light(const Light& other)
	: m_sceneObject(other.m_sceneObject)
	, m_color(other.m_color)
	, m_lightType(other.m_lightType)
{
}

void Light::Render()
{
	if (m_sceneObject)
	{
		m_sceneObject->Render();
	}
}
