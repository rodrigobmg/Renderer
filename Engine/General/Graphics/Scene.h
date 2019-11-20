#pragma once

#include "SceneNode.h"

class Scene
{
public:
	Scene();
	~Scene();

	void SetRootNode(const SceneNodePtr& rootNode) { m_rootNode = rootNode; }
	void Update();
	void Render();
	SceneNodePtr& GetRootNode() { return m_rootNode; }
	bool ContainsNode(SceneNodeType nodeType) const;
	void GetNodesOfType(SceneNodeType nodeType, vector<SceneNodePtr>& nodes);

private:
	SceneNodePtr	m_rootNode;
};