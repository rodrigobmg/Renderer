#include "pch.h"
#include "Light.h"

#include "Material.h"
#include "IGraphics.h"
#include "Loader.h"

#include "Scene.h"
#include "SceneNode.h"
#include "MeshNode.h"

Light::Light()
	: m_color(1.0f)
	, m_intensity(1.0f)
{
}

Light::Light(const Color& color, const IGraphicsPtr& graphics)
	: m_color(color)
	, m_intensity(1.0f)
{
	m_scene = Loader::LoadScene("Assets/pointlight.object", graphics);
	if (m_scene)
	{
		ITexturePtr texture = graphics->CreateTexture(reinterpret_cast<float*>(&m_color), 1, 1, sizeof(float) * 4, TextureFormat::RGBA32f);
		MeshNode* meshNode = static_cast<MeshNode*>(m_scene->GetRootNode()->GetChild(0).get());
		meshNode->GetMaterial(0)->SetDiffuseTexture(texture);
	}
}

Light::Light(const Light& other)
	: m_scene(other.m_scene)
	, m_color(other.m_color)
	, m_intensity(other.m_intensity)
{
}

void Light::Render()
{
	if (m_scene)
	{
		m_scene->Render();
	}
}
