#include "pch.h"
#include "DX11Texture.h"

#include <General/Graphics/IGraphics.h>

DX11Texture::DX11Texture(const DevicePtr& device, const DeviceContextPtr& deviceContext)
	: m_device(device)
	, m_deviceContext(deviceContext)
	, m_texture(nullptr)
	, m_shaderResourceView(nullptr)
{
}

DX11Texture::~DX11Texture()
{
	if (m_shaderResourceView)
	{
		m_shaderResourceView->Release();
		m_shaderResourceView = nullptr;
	}

	if (m_texture)
	{
		m_texture->Release();
		m_texture = nullptr;
	}
}

DXGI_FORMAT GetFormat(TextureFormat format)
{
	switch (format)
	{
	case TextureFormat::RGBA32f:
		return DXGI_FORMAT_R32G32B32A32_FLOAT;
	case TextureFormat::RGB32f:
		return DXGI_FORMAT_R32G32B32_FLOAT;
	case TextureFormat::R8u:
		return DXGI_FORMAT_R8_UINT;
	default:
		assert("Unsupported number of channels");
		return DXGI_FORMAT_UNKNOWN;
	}
}

bool DX11Texture::Initialize(const void* data, UINT width, UINT height, UINT pitch, TextureFormat texFormat)
{
	DXGI_FORMAT format = GetFormat(texFormat);
	if (format == DXGI_FORMAT_UNKNOWN)
	{
		return false;
	}

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = data;
	initData.SysMemPitch = pitch;
	initData.SysMemSlicePitch = 0;

	HRESULT result = m_device->CreateTexture2D(&desc, &initData, &m_texture);

	if (SUCCEEDED(result) && m_texture)
	{
		assert(!m_shaderResourceView);
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
			SRVDesc.Format = format;
			SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			SRVDesc.Texture2D.MipLevels = 1;
			SRVDesc.Texture2D.MostDetailedMip = SRVDesc.Texture2D.MipLevels - 1;

			result = m_device->CreateShaderResourceView(m_texture, &SRVDesc, &m_shaderResourceView);
			if (FAILED(result))
			{
				m_texture->Release();
				ERROR_LOG("Failed to create shader resource view");
				return false;
			}
		}
	}
	else
	{
		ERROR_LOG("Failed to create texture");
		return false;
	}

	return true;
}

void DX11Texture::Bind(unsigned int slot)
{
	m_deviceContext->PSSetShaderResources(slot, 1, &m_shaderResourceView);
}
