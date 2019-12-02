#include "pch.h"
#include "PointLightNode.h"

#include <General/Graphics/PointLight.h>

PointLightNode::PointLightNode(const SharedPtr<PointLight>& pointLight, const string& name)
	: SceneNode(name, SceneNodeType::kPointLight)
	, m_pointLight(pointLight)
{
	Matrix4d parentMatrixInv = Math::MatrixInverse(GetParentMatrix());
	m_localTransform.m_position = m_pointLight->GetPosition() * parentMatrixInv;
}

PointLightNode::~PointLightNode()
{
}

void PointLightNode::Update()
{
	SceneNode::Update();
	m_pointLight->SetPosition(m_localTransform.m_position * m_localToWorld);
}
