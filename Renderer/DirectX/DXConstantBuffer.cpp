#include "DXConstantBuffer.h"
#include <cassert>
#pragma optimize("", off)
DXConstantBuffer::DXConstantBuffer(std::unique_ptr<ID3D11Device>& device, std::unique_ptr<ID3D11DeviceContext>& deviceContext,
	size_t constantBufferSize, int bufferNumber)
	: m_device(device)
	, m_deviceContext(deviceContext)
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

DXConstantBuffer::~DXConstantBuffer()
{
	if (m_buffer)
	{
		m_buffer->Release();
		m_buffer = nullptr;
	}
}
