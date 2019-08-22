#include "DXMesh.h"

#include <General\Loader.h>

DXMesh::DXMesh(std::unique_ptr<ID3D11Device>& device, std::unique_ptr<ID3D11DeviceContext>& deviceContext)
	: m_device(device)
	, m_deviceContext(deviceContext)
	, m_vertexBuffer(nullptr)
	, m_indexBuffer(nullptr)
{
}

DXMesh::~DXMesh()
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

bool DXMesh::Initialize(const std::string& fileName, const IGraphics& graphics)
{
	//Todo: load mesh
	MeshData meshData;
	Loader::LoadMesh(fileName, meshData, graphics);
	
	m_vertices = meshData.m_vertexData;
	m_indices = meshData.m_indexData;

	switch (meshData.m_primitiveType)
	{
	case PrimitiveType::Points:
		m_topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
		break;
	case PrimitiveType::Line:
		m_topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		break;
	case PrimitiveType::LineStrip:
		m_topology = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
		break;
	case PrimitiveType::Triangles:
		m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		break;
	case PrimitiveType::TriangleStrip:
		m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		break;
	default:
		assert("Unsupported topology");
		break;
	}

	return InitializeBuffers();
}

void DXMesh::Render()
{
	unsigned int stride = sizeof(VertexFormat);
	unsigned int offset = 0;

	if (m_deviceContext)
	{
		//Set the vertex buffer to active in the input assembler so it can be rendered
		m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

		//Set the index buffer to active in the input assembler so it can be rendered
		m_deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);

		//Set the type of primitive that should be rendered
		m_deviceContext->IASetPrimitiveTopology(m_topology);
		assert(m_indices);
		m_deviceContext->DrawIndexed(static_cast<UINT>(m_indices->GetIndexCount()), 0, 0);
	}
}

bool DXMesh::InitializeBuffers()
{

	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	//Set up the description of the static vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexFormat) * static_cast<UINT>(m_vertices->GetVertexCount());
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	//Give the subresource struct a pointer to the vertex data
	vertexData.pSysMem = m_vertices->GetVertexData();
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
	indexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(uint16_t) * m_indices->GetIndexCount());
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = m_indices->GetIndexData();
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = m_device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}