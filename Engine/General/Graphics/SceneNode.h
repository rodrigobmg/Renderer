#pragma once
#include <General/Math/Transform.h>

enum class SceneNodeType
{
	kTransform = 0,
	kMesh,
	kLight,
	kCamera
};

class SceneNode
{
public:
	SceneNode(SceneNodeType type = SceneNodeType::kTransform);
	virtual ~SceneNode();

	virtual void Update();

	virtual void Render();

	void SetParent(const SceneNodePtr& parent) { m_parent = parent; }
	void AddChild(const SceneNodePtr& child) { m_children.push_back(child); }
	SceneNodePtr& GetChild(int index);

	Transform				m_localTransform;

private:
	Matrix4d GetParentMatrix() const;

protected:
	SceneNodeWeakPtr		m_parent;
	vector<SceneNodePtr>	m_children;
	Matrix4d				m_localToWorld;
	SceneNodeType			m_type;
};