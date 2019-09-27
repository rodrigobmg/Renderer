#include "stdafx.h"
#include "DX11ObjectConstantBuffer.h"

#include <General/ObjectConstantBuffer.h>

DX11ObjectConstantBuffer::DX11ObjectConstantBuffer(const UniquePtr<ID3D11Device>& device, const UniquePtr<ID3D11DeviceContext>& deviceContext)
	: DX11ConstantBuffer(device, deviceContext, sizeof(ObjectConstantBufferData), 1)
{
}

bool DX11ObjectConstantBuffer::SetData(const void * data)
{
	if (!UpdaBufferData(data))
	{
		return false;
	}

	m_deviceContext->VSSetConstantBuffers(m_bufferNumber, 1, &m_buffer);

	return true;
}
