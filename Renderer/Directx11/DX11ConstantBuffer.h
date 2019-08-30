#pragma once
#include <General/IConstantBuffer.h>

struct ID3D11Buffer;
struct ID3D11Device;
struct ID3D11DeviceContext;
class DX11ConstantBuffer : public IConstantBuffer
{
public:
	DX11ConstantBuffer(std::unique_ptr<ID3D11Device>& device, std::unique_ptr<ID3D11DeviceContext>& deviceContext,
		size_t constantBufferSize, int bufferNumber);
	~DX11ConstantBuffer();

protected:
	std::unique_ptr<ID3D11Device>&			m_device;
	std::unique_ptr<ID3D11DeviceContext>&	m_deviceContext;
	ID3D11Buffer*							m_buffer;
	int										m_bufferNumber;
};