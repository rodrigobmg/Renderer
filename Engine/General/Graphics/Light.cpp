#include "pch.h"
#include "Light.h"

#include "Material.h"
#include "IGraphics.h"
#include "Loader.h"

#include <General/Graphics/SceneObject.h>

Light::Light()
	: m_color(1.0f)
	, m_intensity(1.0f)
{
}

Light::Light(const Color& color, const IGraphicsPtr& graphics)
	: m_color(color)
	, m_intensity(1.0f)
{
	m_sceneObject = Loader::LoadModel("Assets/pointlight.object", graphics);
	if (m_sceneObject)
	{
		ITexturePtr texture = graphics->CreateTexture(reinterpret_cast<float*>(&m_color), 1, 1, sizeof(float) * 4, TextureFormat::RGBA32f);
		m_sceneObject->GetChildren()[0]->GetMaterial(0)->SetDiffuseTexture(texture);
	}
}

Light::Light(const Light& other)
	: m_sceneObject(other.m_sceneObject)
	, m_color(other.m_color)
	, m_intensity(other.m_intensity)
{
}

void Light::Render()
{
	if (m_sceneObject)
	{
		m_sceneObject->Render();
	}
}
