#pragma once
#include <General/Graphics/ISamplerState.h>

class DX11SamplerState : public ISamplerState
{
public:
	DX11SamplerState(const UniquePtr<ID3D11Device>& device, const UniquePtr<ID3D11DeviceContext>& deviceContext);
	~DX11SamplerState();

	virtual bool Initialize() override;
	virtual void Bind() override;

private:
	const UniquePtr<ID3D11Device>&			m_device;
	const UniquePtr<ID3D11DeviceContext>&	m_deviceContext;
	ID3D11SamplerState*						m_sampler;
};
