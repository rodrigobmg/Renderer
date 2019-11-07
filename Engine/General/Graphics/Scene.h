#pragma once

class Scene
{
public:
	Scene();
	~Scene();

	void SetRootNode(const SceneNodePtr& rootNode) { m_rootNode = rootNode; }
	void Update();
	void Render();
	SceneNodePtr& GetRootNode() { return m_rootNode; }

private:
	SceneNodePtr	m_rootNode;
};