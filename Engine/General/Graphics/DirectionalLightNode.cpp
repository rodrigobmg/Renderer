#include "pch.h"
#include "DirectionalLightNode.h"

#include "DirectionalLight.h"

DirectionalLightNode::DirectionalLightNode(const SharedPtr<DirectionalLight>& directionalLight, const string& name)
	: SceneNode(name, SceneNodeType::kDirectionalLight)
	, m_directionalLight(directionalLight)
{
	if (!m_parent.expired())
	{
		const SceneNodePtr& parentNode = m_parent.lock();
		Quaternion parentOrientationInverse = parentNode->m_localTransform.m_orientation.GetInverse();
		Quaternion orientation = m_directionalLight->GetOrientation();
		m_localTransform.m_orientation = orientation * parentOrientationInverse;
	}
}

DirectionalLightNode::~DirectionalLightNode()
{
}

void DirectionalLightNode::Update()
{
	SceneNode::Update();
	Quaternion parentOrientation;
	if (!m_parent.expired())
	{
		const SceneNodePtr& parentNode = m_parent.lock();
		parentOrientation = parentNode->m_localTransform.m_orientation;
	}
	m_directionalLight->SetOrientation(m_localTransform.m_orientation * parentOrientation);
}
