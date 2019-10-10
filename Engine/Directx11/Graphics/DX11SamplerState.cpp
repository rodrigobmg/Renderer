#include "pch.h"
#include "DX11SamplerState.h"

DX11SamplerState::DX11SamplerState(const UniquePtr<ID3D11Device>& device, const UniquePtr<ID3D11DeviceContext>& deviceContext)
	: m_device(device)
	, m_deviceContext(deviceContext)
	, m_sampler(nullptr)
{
}

DX11SamplerState::~DX11SamplerState()
{
	if (m_sampler)
	{
		m_sampler->Release();
		m_sampler = nullptr;
	}
}

bool DX11SamplerState::Initialize()
{
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	HRESULT result = m_device->CreateSamplerState(&samplerDesc, &m_sampler);
	if (SUCCEEDED(result))
	{
		return true;
	}

	ERROR_LOG("Error creating sampler state");
	return false;
}

void DX11SamplerState::Bind()
{
	if (m_sampler)
	{
		m_deviceContext->PSSetSamplers(0, 1, &m_sampler);
	}
}
