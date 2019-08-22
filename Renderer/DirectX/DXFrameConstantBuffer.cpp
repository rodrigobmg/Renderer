#include "DXFrameConstantBuffer.h"

DXFrameConstantBuffer::DXFrameConstantBuffer(std::unique_ptr<ID3D11Device>& device, std::unique_ptr<ID3D11DeviceContext>& deviceContext)
	: DXConstantBuffer(device, deviceContext, sizeof(FrameConstantBufferData), 0)
{
}

DXFrameConstantBuffer::~DXFrameConstantBuffer()
{
}

bool DXFrameConstantBuffer::SetData(const void * data)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	FrameConstantBufferData* targetData;
	unsigned int bufferNumber;
	const FrameConstantBufferData* sourceData = reinterpret_cast<const FrameConstantBufferData*>(data);

	// Lock the constant buffer so it can be written to.
	result = m_deviceContext->Map(m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	targetData = reinterpret_cast<FrameConstantBufferData*>(mappedResource.pData);
	*targetData = *sourceData;

	// Unlock the constant buffer.
	m_deviceContext->Unmap(m_buffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Finally set the constant buffer in the vertex shader with the updated values.
	m_deviceContext->VSSetConstantBuffers(m_bufferNumber, 1, &m_buffer);

	return true;
}
