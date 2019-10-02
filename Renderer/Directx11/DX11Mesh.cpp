#include "stdafx.h"
#include "DX11Mesh.h"

#include <General\Loader.h>

DX11Mesh::DX11Mesh(const UniquePtr<ID3D11Device>& device, const UniquePtr<ID3D11DeviceContext>& deviceContext, const IVertexArrayPtr& vertexArray, const IIndexArrayPtr& indexArray, PrimitiveType type)
	: m_device(device)
	, m_deviceContext(deviceContext)
	, m_vertices(vertexArray)
	, m_indices(indexArray)
	, m_vertexBuffer(nullptr)
	, m_indexBuffer(nullptr)
{
	switch (type)
	{
	case PrimitiveType::Point:
		m_topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
		break;
	case PrimitiveType::Line:
		m_topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		break;
	case PrimitiveType::Triangle:
		m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		break;
	default:
		assert("Unsupported topology");
		break;
	}
}

DX11Mesh::~DX11Mesh()
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

bool DX11Mesh::Initialize()
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	//Set up the description of the static vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = static_cast<UINT>(m_vertices->GetBufferSize());
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

void DX11Mesh::Render()
{
	UINT stride = static_cast<UINT>(m_vertices->GetStride());
	UINT offset = 0;

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