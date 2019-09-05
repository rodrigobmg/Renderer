#include "SceneObject.h"
#include "IMesh.h"
#include "IConstantBuffer.h"
#include "ObjectConstantBuffer.h"
#include "Material.h"

SceneObject::SceneObject()
	: m_mesh(nullptr)
	, m_material(nullptr)
	, m_objectConstantBuffer(nullptr)
	, m_objectConstantBufferData(new ObjectConstantBufferData())
{
}

SceneObject::SceneObject(SharedPtr<IMesh>& mesh, SharedPtr<Material>& material, SharedPtr<IConstantBuffer>& constantBuffer)
	: m_mesh(mesh)
	, m_material(material)
	, m_objectConstantBuffer(constantBuffer)
	, m_objectConstantBufferData(new ObjectConstantBufferData())
{
}

SceneObject::~SceneObject()
{
	delete m_objectConstantBufferData;
}

void SceneObject::Render()
{
	m_objectConstantBufferData->m_model = MatrixTranspose(m_transform.GetMatrix());
	m_objectConstantBufferData->m_modelInverseTranspose = MatrixInverse(MatrixTranspose(m_objectConstantBufferData->m_model));
	m_objectConstantBuffer->SetData(m_objectConstantBufferData);

	if (m_material)
	{
		m_material->Render();
	}

	if (m_mesh)
	{
		m_mesh->Render();
	}
}
