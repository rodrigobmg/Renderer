#include "DX11FrameConstantBuffer.h"

DX11FrameConstantBuffer::DX11FrameConstantBuffer(std::unique_ptr<ID3D11Device>& device, std::unique_ptr<ID3D11DeviceContext>& deviceContext)
	: DX11ConstantBuffer(device, deviceContext, sizeof(FrameConstantBufferData), 0)
{
}

DX11FrameConstantBuffer::~DX11FrameConstantBuffer()
{
}

bool DX11FrameConstantBuffer::SetData(const void * data)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	FrameConstantBufferData* targetData;
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

	// Finally set the constant buffer in the vertex shader with the updated values.
	m_deviceContext->VSSetConstantBuffers(m_bufferNumber, 1, &m_buffer);
	m_deviceContext->PSSetConstantBuffers(m_bufferNumber, 1, &m_buffer);

	return true;
}
