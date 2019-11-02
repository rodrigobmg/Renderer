#pragma once

class TextureManager
{
public:
	TextureManager(const IGraphics& graphics);
	~TextureManager();

	ITexturePtr GetTexture(const string& path);

private:
	const IGraphics&				m_graphics;
	std::map<string, ITexturePtr>	m_textureMap;
};