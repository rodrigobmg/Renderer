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
	bool UpdaBufferData(const void* sourceData);

	const DevicePtr&		m_device;
	const DeviceContextPtr&	m_deviceContext;
	ID3D11Buffer*			m_buffer;
	size_t					m_bufferSize;
	int						m_bufferNumber;
};