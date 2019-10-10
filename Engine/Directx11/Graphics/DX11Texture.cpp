#include "pch.h"
#include "DX11Texture.h"

#include <General/Graphics/Bitmap.h>

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

DXGI_FORMAT GetFormat(int numChannels)
{
	switch (numChannels)
	{
	case 1:
		return DXGI_FORMAT_R32_FLOAT;
	case 2:
		return DXGI_FORMAT_R32G32_FLOAT;
	case 3:
		return DXGI_FORMAT_R32G32B32_FLOAT;
	case 4:
		return DXGI_FORMAT_R32G32B32A32_FLOAT;
	default:
		assert("Unsupported number of channels");
		return DXGI_FORMAT_UNKNOWN;
	}
}

bool DX11Texture::Initialize(const BitmapPtr& bitmap)
{
	DXGI_FORMAT format = GetFormat(bitmap->GetNumChannels());
	if (format == DXGI_FORMAT_UNKNOWN)
	{
		return false;
	}

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = bitmap->GetWidth();
	desc.Height = bitmap->GetHeight();
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
	initData.pSysMem = bitmap->GetData();
	initData.SysMemPitch = static_cast<UINT>(bitmap->GetPitch());
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
