#pragma once
#include <General/Graphics/ITexture.h>

class DX11Texture : public ITexture
{
public:
	DX11Texture(const DevicePtr& device, const DeviceContextPtr& deviceContext);
	~DX11Texture();

	virtual bool Initialize(const BitmapPtr& bitmap) override;
	virtual void Bind(unsigned int slot) override;

private:
	const DevicePtr&			m_device;
	const DeviceContextPtr&		m_deviceContext;
	ID3D11Texture2D*			m_texture;
	ID3D11ShaderResourceView*	m_shaderResourceView;
};