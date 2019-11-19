#include "pch.h"
#include "PointLightNode.h"

PointLightNode::PointLightNode(const SharedPtr<PointLight>& pointLight, const string& name)
	: SceneNode(name, SceneNodeType::kPointLight)
	, m_pointLight(pointLight)
{
}

PointLightNode::~PointLightNode()
{
}

void PointLightNode::Update()
{
}

void PointLightNode::Render()
{
}
