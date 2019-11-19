#include "pch.h"
#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Update()
{
	m_rootNode->Update();
}

void Scene::Render()
{
	m_rootNode->Render();
}

bool Scene::ContainsNode(SceneNodeType nodeType) const
{
	return m_rootNode->ContainsNode(nodeType);
}

void Scene::GetNodesOfType(SceneNodeType nodeType, vector<const SceneNode*>& nodes) const
{
	m_rootNode->GetNodesOfType(nodeType, nodes);
}
