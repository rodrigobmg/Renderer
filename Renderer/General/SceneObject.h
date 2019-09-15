#pragma once
#include <General/Transform.h>

class SceneObject
{
public:
	SceneObject();
	SceneObject(const SceneObject&) = delete;
	SceneObject(const vector<MeshPtr>& meshes, const vector<MaterialPtr>& materials, const ConstantBufferPtr& objectConstantBuffer);
	~SceneObject();

	void Render();

	void AddChild(const SceneObjectPtr& sceneObject);
	void SetParent(const SceneObjectPtr& sceneObject) { m_parent = sceneObject; }
	const SceneObjectWeakPtr& GetParent() const { return m_parent; }
	void SetMeshData(const vector<MeshPtr>& meshes, const vector<MaterialPtr>& materials, const ConstantBufferPtr& constBuffer);

private:
	Matrix4d GetParentMatrix() const;

	vector<SceneObjectPtr>		m_children;
	SceneObjectWeakPtr			m_parent;
	vector<MeshPtr>				m_meshes;
	vector<MaterialPtr>			m_materials;
	ConstantBufferPtr			m_objectConstantBuffer;
	ObjectConstantBufferData*	m_objectConstantBufferData;

public:
	Transform					m_transform;
};