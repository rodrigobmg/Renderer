#include "stdafx.h"
#include "DX11MaterialConstantBuffer.h"

#include <General/MaterialConstantBuffer.h>

DX11MaterialConstantBuffer::DX11MaterialConstantBuffer(const UniquePtr<ID3D11Device>& device, const UniquePtr<ID3D11DeviceContext>& deviceContext)
	: DX11ConstantBuffer(device, deviceContext, sizeof(MaterialConstantBufferData), 2)
{
}

bool DX11MaterialConstantBuffer::SetData(const void* data)
{
	if (!UpdaBufferData(data))
	{
		return false;
	}

	m_deviceContext->PSSetConstantBuffers(m_bufferNumber, 1, &m_buffer);

	return true;
}
