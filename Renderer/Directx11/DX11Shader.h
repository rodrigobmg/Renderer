#pragma once

#include <General/IShader.h>

struct ID3D11VertexShader;
struct ID3D11DeviceContext;
struct ID3D11Device;
struct ID3D11InputLayout;
struct ID3D11PixelShader;
class DX11Shader : public IShader
{
public:
	DX11Shader(UniquePtr<ID3D11DeviceContext>& deviceContext, UniquePtr<ID3D11Device>& device, ShaderType type);
	DX11Shader(const DX11Shader&) = delete;
	~DX11Shader();

	virtual bool Initialize(const char* shaderFilePath) override;
	virtual void Render() override;

private:
	UniquePtr<ID3D11DeviceContext>&	m_deviceContext;
	UniquePtr<ID3D11Device>&		m_device;
	ID3D11VertexShader*				m_vertexShader;
	ID3D11PixelShader*				m_pixelShader;
	ID3D11InputLayout*				m_layout;
	ShaderType						m_type;
};
