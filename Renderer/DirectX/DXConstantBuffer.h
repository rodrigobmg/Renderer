#pragma once
#include <memory>
#include <d3d11.h>

struct ID3D11Buffer;
struct ID3D11Device;
struct ID3D11DeviceContext;
class DXConstantBuffer
{
public:
	DXConstantBuffer(std::unique_ptr<ID3D11Device>& device, std::unique_ptr<ID3D11DeviceContext>& deviceContext,
		size_t constantBufferSize, int bufferNumber);
	~DXConstantBuffer();

protected:
	std::unique_ptr<ID3D11Device>&			m_device;
	std::unique_ptr<ID3D11DeviceContext>&	m_deviceContext;
	ID3D11Buffer*							m_buffer;
	int										m_bufferNumber;
};