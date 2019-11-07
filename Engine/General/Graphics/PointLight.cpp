#include "pch.h"
#include "PointLight.h"

#include "Scene.h"
#include "SceneNode.h"


PointLight::PointLight()
	: Light()
	, m_position(0.0f)
	, m_worldPosition(0.f)
{
}

PointLight::PointLight(const Color& color, const Vector3d& position, const IGraphicsPtr& graphics)
	: Light(color, graphics)
	, m_position(position)
	, m_worldPosition(position)
{
	if (m_scene)
	{
		m_scene->GetRootNode()->m_localTransform.m_position = m_position;
	}
}

PointLight::PointLight(const PointLight& other)
	: Light(other)
	, m_rotationAroundOrigin(other.m_rotationAroundOrigin)
	, m_position(other.m_position)
	, m_worldPosition(other.m_worldPosition)
{
}

void PointLight::SetPosition(const Vector3d& position)
{
	m_position = position;
	m_worldPosition = m_position;
	if (m_scene)
	{
		m_scene->GetRootNode()->m_localTransform.m_position = m_worldPosition;
	}
	m_rotationAroundOrigin = Quaternion();
}

void PointLight::SetRotationAroundOrigin(const Quaternion& rotation)
{
	m_rotationAroundOrigin = rotation;
	m_worldPosition = m_position * m_rotationAroundOrigin;
	if (m_scene)
	{
		m_scene->GetRootNode()->m_localTransform.m_position = m_worldPosition;
	}
}
