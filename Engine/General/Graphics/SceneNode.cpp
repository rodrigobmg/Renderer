#include "pch.h"
#include "SceneNode.h"

SceneNode::SceneNode(SceneNodeType type)
	: m_type(type)
{
}

SceneNode::~SceneNode()
{
}

void SceneNode::Update()
{
	m_localToWorld = GetParentMatrix() * m_localTransform.GetMatrix();
	for (SceneNodePtr& sceneNode : m_children)
	{
		sceneNode->Update();
	}
}

void SceneNode::Render()
{
	for (SceneNodePtr& sceneNode : m_children)
	{
		sceneNode->Render();
	}
}

SceneNodePtr& SceneNode::GetChild(int index)
{
	assert(index < m_children.size());
	return m_children[index];
}

Matrix4d SceneNode::GetParentMatrix() const
{
	Matrix4d matrix = Matrix4d::Identity();
	if (!m_parent.expired())
	{
		SceneNodePtr node = m_parent.lock();
		return node->m_localToWorld;
	}
	return matrix;
}
