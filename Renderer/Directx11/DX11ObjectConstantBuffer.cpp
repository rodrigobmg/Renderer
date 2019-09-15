#include "stdafx.h"
#include "DX11ObjectConstantBuffer.h"

DX11ObjectConstantBuffer::DX11ObjectConstantBuffer(const UniquePtr<ID3D11Device>& device, const UniquePtr<ID3D11DeviceContext>& deviceContext)
	: DX11ConstantBuffer(device, deviceContext, sizeof(ObjectConstantBufferData), 1)
{
}

DX11ObjectConstantBuffer::~DX11ObjectConstantBuffer()
{
	DX11ConstantBuffer::~DX11ConstantBuffer();
}

bool DX11ObjectConstantBuffer::SetData(const void * data)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ObjectConstantBufferData* targetData;
	unsigned int bufferNumber;
	const ObjectConstantBufferData* sourceData = reinterpret_cast<const ObjectConstantBufferData*>(data);

	// Lock the constant buffer so it can be written to.
	result = m_deviceContext->Map(m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	targetData = reinterpret_cast<ObjectConstantBufferData*>(mappedResource.pData);
	*targetData = *sourceData;

	// Unlock the constant buffer.
	m_deviceContext->Unmap(m_buffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Finally set the constant buffer in the vertex shader with the updated values.
	m_deviceContext->VSSetConstantBuffers(m_bufferNumber, 1, &m_buffer);

	return true;
}
