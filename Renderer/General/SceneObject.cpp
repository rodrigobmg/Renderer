#include "stdafx.h"
#include "SceneObject.h"
#include "IMesh.h"
#include "IConstantBuffer.h"
#include "ObjectConstantBuffer.h"
#include "Material.h"

SceneObject::SceneObject()
	: m_objectConstantBuffer(nullptr)
	, m_objectConstantBufferData(nullptr)
{
}

SceneObject::SceneObject(const vector<MeshPtr>& meshes, const vector<MaterialPtr>& materials, const ConstantBufferPtr& objectConstantBuffer)
	: m_meshes(meshes)
	, m_materials(materials)
	, m_objectConstantBuffer(objectConstantBuffer)
	, m_objectConstantBufferData(new ObjectConstantBufferData())
{
	assert(m_meshes.size() == m_materials.size());
	assert(!m_meshes.empty() && objectConstantBuffer);
}

SceneObject::~SceneObject()
{
	if (m_objectConstantBufferData)
	{
		delete m_objectConstantBufferData;
	}
}

void SceneObject::Render()
{
	if (m_objectConstantBufferData)
	{
		m_objectConstantBufferData->m_model = MatrixTranspose(GetParentMatrix() * m_transform.GetMatrix());
		m_objectConstantBufferData->m_modelInverseTranspose = MatrixInverse(MatrixTranspose(m_objectConstantBufferData->m_model));
		m_objectConstantBuffer->SetData(m_objectConstantBufferData);
	}

	for (int i = 0; i < m_meshes.size(); i++)
	{
		m_materials[i]->Render();
		m_meshes[i]->Render();
	}

	for (SceneObjectPtr& sceneObject : m_children)
	{
		sceneObject->Render();
	}
}

void SceneObject::AddChild(const SceneObjectPtr& sceneObject)
{
	assert(!sceneObject->GetParent().expired());
	assert(sceneObject->GetParent().lock().get() == this);
	m_children.push_back(sceneObject);
}

void SceneObject::SetMeshData(const vector<MeshPtr>& meshes, const vector<MaterialPtr>& materials, const ConstantBufferPtr& constBuffer)
{
	m_meshes = meshes;
	m_materials = materials;
	m_objectConstantBuffer = constBuffer;
	if (!m_objectConstantBufferData)
	{
		m_objectConstantBufferData = new ObjectConstantBufferData();
	}
}

Matrix4d SceneObject::GetParentMatrix() const
{
	Matrix4d matrix = Matrix4d::Identity();
	if (!m_parent.expired())
	{
		SceneObjectPtr node = m_parent.lock();
		while (node)
		{
			matrix = matrix * node->m_transform.GetMatrix();
			if (node->m_parent.expired())
			{
				break;
			}
			node = node->m_parent.lock();
		}
	}

	return matrix;
}
