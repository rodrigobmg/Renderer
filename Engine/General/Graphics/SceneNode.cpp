#include "pch.h"
#include "SceneNode.h"

SceneNode::SceneNode(const string& name, SceneNodeType type)
	: m_name(name)
	, m_type(type)
{
}

SceneNode::~SceneNode()
{
}

void SceneNode::Update()
{
	m_localToWorld = m_localTransform.GetMatrix() * GetParentMatrix();
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

bool SceneNode::ContainsNode(SceneNodeType type) const
{
	if (m_type == type)
	{
		return true;
	}

	for (const SceneNodePtr& child : m_children)
	{
		if (child->ContainsNode(type))
		{
			return true;
		}
	}

	return false;
}

void SceneNode::GetNodesOfType(SceneNodeType type, vector<SceneNodePtr>& nodes)
{
	for (const SceneNodePtr& child : m_children)
	{
		if (child->GetType() == type)
		{
			nodes.push_back(child);
		}
		child->GetNodesOfType(type, nodes);
	}
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
