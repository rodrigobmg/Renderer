#include "pch.h"
#include "PointLight.h"

#include "SceneObject.h"
#include "Material.h"
#include "Bitmap.h"
#include "IGraphics.h"

#include <General/Math/Color.h>

PointLight::PointLight()
	: Light(LightType::kPoint)
	, m_position(0.0f)
{
}

PointLight::PointLight(const Color & color, const Vector3d & position, const IGraphicsPtr& graphics)
	: Light(color, graphics, LightType::kPoint)
	, m_position(position)
	, m_worldPosition(position)
{
	BitmapPtr diffuse(new Bitmap());
	diffuse->Alloc(reinterpret_cast<float*>(&m_color), 1, 1, 4, Bitmap::DataFormat::FLOAT);
	m_sceneObject->GetChildren()[0]->GetMaterial(0)->SetDiffuseTexture(graphics->CreateTexture(diffuse));
	m_sceneObject->m_transform.m_position = m_position;
}

PointLight::PointLight(const PointLight& other)
	: Light(other)
	, m_position(other.m_position)
	, m_worldPosition(other.m_worldPosition)
{
}

void PointLight::SetPosition(const Vector3d& position)
{
	m_position = position;
	m_worldPosition = m_position;
	m_sceneObject->m_transform.m_position = m_worldPosition;
	m_rotationAroundOrigin = Quaternion();
}

void PointLight::SetRotationAroundOrigin(const Quaternion& rotation)
{
	m_rotationAroundOrigin = rotation;
	m_worldPosition = m_position * m_rotationAroundOrigin;
	m_sceneObject->m_transform.m_position = m_worldPosition;
}
