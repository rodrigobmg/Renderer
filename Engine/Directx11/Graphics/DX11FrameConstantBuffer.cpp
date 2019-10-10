#include "pch.h"
#include "DX11FrameConstantBuffer.h"

DX11FrameConstantBuffer::DX11FrameConstantBuffer(UniquePtr<ID3D11Device>& device, UniquePtr<ID3D11DeviceContext>& deviceContext)
	: DX11ConstantBuffer(device, deviceContext, sizeof(FrameConstantBufferData), 0)
{
}

bool DX11FrameConstantBuffer::SetData(const void * data)
{
	if (!UpdaBufferData(data))
	{
		return false;
	}

	m_deviceContext->VSSetConstantBuffers(m_bufferNumber, 1, &m_buffer);
	m_deviceContext->PSSetConstantBuffers(m_bufferNumber, 1, &m_buffer);

	return true;
}
