#pragma once

class ITexture
{
public:
	virtual ~ITexture() {}

	virtual bool Initialize(const BitmapPtr& bitmap) = 0;
	virtual void Bind(unsigned int slot) = 0;
};