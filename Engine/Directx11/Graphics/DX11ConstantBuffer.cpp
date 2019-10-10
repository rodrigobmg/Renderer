#include "pch.h"

#include "DX11ConstantBuffer.h"

DX11ConstantBuffer::DX11ConstantBuffer(const DevicePtr& device, const DeviceContextPtr& deviceContext, size_t constantBufferSize, int bufferNumber)
	: m_device(device)
	, m_deviceContext(deviceContext)
	, m_bufferSize(constantBufferSize)
	, m_bufferNumber(bufferNumber)
{
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = static_cast<UINT>(constantBufferSize);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer
	HRESULT result = m_device->CreateBuffer(&bufferDesc, NULL, &m_buffer);
	assert(SUCCEEDED(result));
}

DX11ConstantBuffer::~DX11ConstantBuffer()
{
	if (m_buffer)
	{
		m_buffer->Release();
		m_buffer = nullptr;
	}
}

bool DX11ConstantBuffer::UpdaBufferData(const void* sourceData)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	// Lock the constant buffer so it can be written to.
	HRESULT result = m_deviceContext->Map(m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	//Copy the data
	memcpy(mappedResource.pData, sourceData, m_bufferSize);

	// Unlock the constant buffer.
	m_deviceContext->Unmap(m_buffer, 0);

	return true;
}
