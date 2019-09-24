#pragma once
#include <General/IConstantBuffer.h>

struct ID3D11Buffer;
struct ID3D11Device;
struct ID3D11DeviceContext;
class DX11ConstantBuffer : public IConstantBuffer
{
public:
	DX11ConstantBuffer(const DevicePtr& device, const DeviceContextPtr& deviceContext,
		size_t constantBufferSize, int bufferNumber);
	~DX11ConstantBuffer();

protected:
	const DevicePtr&		m_device;
	const DeviceContextPtr&	m_deviceContext;
	ID3D11Buffer*			m_buffer;
	int						m_bufferNumber;
};