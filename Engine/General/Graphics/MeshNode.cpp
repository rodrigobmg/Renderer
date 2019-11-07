#include "pch.h"
#include "MeshNode.h"

#include "IMesh.h"
#include "IConstantBuffer.h"
#include "ObjectConstantBuffer.h"
#include "Material.h"

MeshNode::MeshNode(const vector<IMeshPtr>& meshes, const vector<MaterialPtr>& materials, const IConstantBufferPtr& objectConstantBuffer)
	: SceneNode(SceneNodeType::kMesh)
	, m_meshes(meshes)
	, m_materials(materials)
	, m_objectConstantBuffer(objectConstantBuffer)
	, m_objectConstantBufferData(new ObjectConstantBufferData)
{
}

MeshNode::~MeshNode()
{
	if (m_objectConstantBufferData)
	{
		delete m_objectConstantBufferData;
	}
}

void MeshNode::Render()
{
	if (m_objectConstantBufferData)
	{
		m_objectConstantBufferData->m_model = MatrixTranspose(m_localToWorld);
		m_objectConstantBufferData->m_modelInverseTranspose = MatrixInverse(MatrixTranspose(m_objectConstantBufferData->m_model));
		m_objectConstantBuffer->SetData(m_objectConstantBufferData);
	}

	for (int i = 0; i < m_meshes.size(); i++)
	{
		m_materials[i]->Render();
		m_meshes[i]->Render();
	}

	SceneNode::Render();
}

MaterialPtr& MeshNode::GetMaterial(int index)
{
	assert(index < m_materials.size());
	return m_materials[index];
}
