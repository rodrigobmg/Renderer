#pragma once
#include <General/Transform.h>

class SceneObject
{
public:
	SceneObject();
	SceneObject(const SceneObject&) = delete;
	SceneObject(const vector<IMeshPtr>& meshes, const vector<MaterialPtr>& materials, const IConstantBufferPtr& objectConstantBuffer);
	~SceneObject();

	void Render();

	void AddChild(const SceneObjectPtr& sceneObject);
	void SetParent(const SceneObjectPtr& sceneObject) { m_parent = sceneObject; }
	const SceneObjectWeakPtr& GetParent() const { return m_parent; }
	void SetMeshData(const vector<IMeshPtr>& meshes, const vector<MaterialPtr>& materials, const IConstantBufferPtr& constBuffer);
	size_t GetNumMaterials() const { return m_materials.size(); }
	const MaterialPtr GetMaterial(int index) const;
	const vector<SceneObjectPtr>& GetChildren() const { return m_children; }

private:
	Matrix4d GetParentMatrix() const;

	vector<SceneObjectPtr>		m_children;
	SceneObjectWeakPtr			m_parent;
	vector<IMeshPtr>			m_meshes;
	vector<MaterialPtr>			m_materials;
	IConstantBufferPtr			m_objectConstantBuffer;
	ObjectConstantBufferData*	m_objectConstantBufferData;

public:
	Transform					m_transform;
};