#pragma once

#include "SceneNode.h"

class MeshNode : public SceneNode
{
public:
	MeshNode(const vector<IMeshPtr>& meshes, const vector<MaterialPtr>& materials, const IConstantBufferPtr& objectConstantBuffer, const string& name);
	virtual ~MeshNode();

	virtual void Render() override;
	MaterialPtr& GetMaterial(int index);

public:
	vector<IMeshPtr>			m_meshes;
	vector<MaterialPtr>			m_materials;
	IConstantBufferPtr			m_objectConstantBuffer;
	ObjectConstantBufferData*	m_objectConstantBufferData;
};