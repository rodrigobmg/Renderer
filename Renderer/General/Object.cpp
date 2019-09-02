#include "Object.h"
#include "IMesh.h"
#include "IConstantBuffer.h"
#include "ObjectConstantBuffer.h"
#include "Material.h"

Core::Object::Object()
	: m_mesh(nullptr)
	, m_material(nullptr)
	, m_objectConstantBuffer(nullptr)
	, m_objectConstantBufferData(new ObjectConstantBufferData())
{
}

Core::Object::Object(SharedPtr<IMesh>& mesh, SharedPtr<Material>& material, SharedPtr<IConstantBuffer>& constantBuffer)
	: m_mesh(mesh)
	, m_material(material)
	, m_objectConstantBuffer(constantBuffer)
	, m_objectConstantBufferData(new ObjectConstantBufferData())
{
}

Core::Object::~Object()
{
	delete m_objectConstantBufferData;
}

void Core::Object::Render()
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
