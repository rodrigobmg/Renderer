#include "pch.h"
#include "Scene.h"

#include "SceneNode.h"

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
