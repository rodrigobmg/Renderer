#include "DXMesh.h"

DXMesh::DXMesh(const SmartPointer<ID3D11Device>& device, ID3D11DeviceContext* deviceContext)
	:m_device(device),
	m_deviceContext(deviceContext),
	m_vertexBuffer(nullptr),
	m_indexBuffer(nullptr),
	m_vertexCount(0),
	m_indexCount(0)
{
}

DXMesh::DXMesh(DXMesh & other)
{
}

bool DXMesh::Initialize()
{
	return InitializeBuffers();
}

void DXMesh::Shutdown()
{
	ShutdownBuffers();
}

void DXMesh::Render()
{
	RenderBuffers();
}

bool DXMesh::InitializeBuffers()
{

	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	m_vertexCount = 3;
	m_indexCount = 3;

	VertexType* vertices = new VertexType[m_vertexCount];
	unsigned long* indices = new unsigned long[m_indexCount];

	using namespace Math;

	vertices[0].position = Vector3d(-1.0f, -1.0f, 0.0f);
	vertices[0].color = Vector4d(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[1].position = Vector3d(0.0f, 1.0f, 0.0f);
	vertices[1].color = Vector4d(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position = Vector3d(1.0f, -1.0f, 0.0f);
	vertices[2].color = Vector4d(0.0f, 1.0f, 0.0f, 1.0f);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	//Set up the description of the static vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	//Give the subresource struct a pointer to the vertex data
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	//Create the vertex buffer
	HRESULT result = m_device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//Set up the description of the static index buffer
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = m_device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//Release the arrays
	delete[] vertices;
	delete[] indices;

	return true;
}

void DXMesh::ShutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = nullptr;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = nullptr;
	}
}

void DXMesh::RenderBuffers()
{
	unsigned int stride = sizeof(VertexType);
	unsigned int offset = 0;

	if (m_deviceContext)
	{
		//Set the vertex buffer to active in the input assembler so it can be rendered
		m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

		//Set the index buffer to active in the input assembler so it can be rendered
		m_deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		//Set the type of primitive that should be rendered from this vertex buffer in this case triangles
		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}
