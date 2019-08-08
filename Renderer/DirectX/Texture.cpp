#include "Texture.h"
#include "DirectXTex.h"
#include <memory>

Texture::Texture()
	:m_texture(nullptr)
{
}

Texture::Texture(const Texture & texture)
{
}

Texture::~Texture()
{
}

bool Texture::Initialize(ID3D11Device * device, WCHAR * fileName)
{
	HRESULT result;

	// Load the texture in.
	using namespace DirectX;
	TexMetadata info;
	auto image = std::make_unique<ScratchImage>();
	result = LoadFromDDSFile(fileName, DDS_FLAGS_NONE, &info, *image);
	if (FAILED(result))
	{
		return false;
	}

	result = CreateShaderResourceView(device, image->GetImage(0, 0, 0), 1, info, &m_texture);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void Texture::Shutdown()
{
	// Release the texture resource.
	if (m_texture)
	{
		m_texture->Release();
		m_texture = nullptr;
	}
}

ID3D11ShaderResourceView * Texture::GetTexture()
{
	return m_texture;
}
