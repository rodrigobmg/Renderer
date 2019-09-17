#pragma once
#include "ITexture.h"

class Texture : public ITexture
{
public:
	Texture();
	Texture(const Texture& texture) = delete;
	~Texture();

	virtual void Bind() override {}

private:
	ID3D11ShaderResourceView* m_texture;
};