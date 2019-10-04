#pragma once

#include <General/IShader.h>

class DX11Shader : public IShader
{
public:
	DX11Shader(const UniquePtr<ID3D11Device>& device, const UniquePtr<ID3D11DeviceContext>& deviceContext, ShaderType type);
	DX11Shader(const DX11Shader&) = delete;
	~DX11Shader();

	virtual bool Initialize(const char* shaderFilePath, const IVertexArrayPtr& vertexArray) override;
	virtual void Render() override;

private:
	const UniquePtr<ID3D11Device>&			m_device;
	const UniquePtr<ID3D11DeviceContext>&	m_deviceContext;
	ID3D11VertexShader*						m_vertexShader;
	ID3D11PixelShader*						m_pixelShader;
	ID3D11InputLayout*						m_layout;
	ShaderType								m_type;
};
