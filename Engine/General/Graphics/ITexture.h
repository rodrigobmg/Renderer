#pragma once

#include "IGraphics.h"

class ITexture
{
public:
	virtual ~ITexture() {}

	virtual bool Initialize(const void* data, UINT width, UINT height, UINT pitch, TextureFormat format) = 0;
	virtual void Bind(unsigned int slot) = 0;
};