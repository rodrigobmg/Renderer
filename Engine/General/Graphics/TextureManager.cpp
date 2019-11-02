#include "pch.h"
#include "TextureManager.h"

#include "IGraphics.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

TextureManager::TextureManager(const IGraphics& graphics)
	: m_graphics(graphics)
{
}

TextureManager::~TextureManager()
{
	m_textureMap.clear();
}

static const int kRequiredNumberOfComponents = 4;
ITexturePtr TextureManager::GetTexture(const string& path)
{
	if (m_textureMap[path])
	{
		return m_textureMap[path];
	}
	else
	{
		int width, height, channels;
		float* data = stbi_loadf(path.c_str(), &width, &height, &channels, kRequiredNumberOfComponents);
		if (data)
		{
			ITexturePtr texture = m_graphics.CreateTexture(data, width, height, sizeof(float) * width * kRequiredNumberOfComponents, TextureFormat::RGBA32f);
			stbi_image_free(data);
			if (texture)
			{
				m_textureMap[path] = texture;
				return m_textureMap[path];
			}
		}
		else
		{
			ERROR_LOG("Failed to load texture: {}", path);
		}
	}
	return nullptr;
}
