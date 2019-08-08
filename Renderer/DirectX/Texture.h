#pragma once
#include <d3d11.h>

class Texture
{
public:
	Texture();
	Texture(const Texture& texture);
	~Texture();

	bool Initialize(ID3D11Device* device, WCHAR* fileName);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

private:
	ID3D11ShaderResourceView* m_texture;
};