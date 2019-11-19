#pragma once
#include <General/Math/Transform.h>

enum class SceneNodeType
{
	kTransform = 0,
	kMesh,
	kPointLight,
	kCamera
};

class SceneNode
{
public:
	SceneNode(const string& name, SceneNodeType type = SceneNodeType::kTransform);
	virtual ~SceneNode();

	virtual void Update();
	virtual void Render();

	void SetParent(const SceneNodePtr& parent) { m_parent = parent; }
	void AddChild(const SceneNodePtr& child) { m_children.push_back(child); }
	SceneNodePtr& GetChild(int index);
	bool ContainsNode(SceneNodeType type) const;
	void GetNodesOfType(SceneNodeType type, vector<const SceneNode*>& nodes) const;
	SceneNodeType GetType() const { return m_type; }

	Transform				m_localTransform;

private:
	Matrix4d GetParentMatrix() const;

protected:
	SceneNodeWeakPtr		m_parent;
	vector<SceneNodePtr>	m_children;
	Matrix4d				m_localToWorld;
	string					m_name;
	SceneNodeType			m_type;
};