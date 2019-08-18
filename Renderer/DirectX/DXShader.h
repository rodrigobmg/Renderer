#pragma once

#include <General/IShader.h>
#include <memory>

struct ID3D11VertexShader;
struct ID3D11DeviceContext;
struct ID3D11Device;
struct ID3D11InputLayout;
struct ID3D11PixelShader;
class DXShader : public IShader
{
public:
	DXShader(std::unique_ptr<ID3D11DeviceContext>& deviceContext, std::unique_ptr<ID3D11Device>& device, ShaderType type);
	DXShader(const DXShader&) = delete;
	~DXShader();

	virtual bool Initialize(const char* shaderFilePath) override;
	virtual void Render() override;

private:
	std::unique_ptr<ID3D11DeviceContext>&	m_deviceContext;
	std::unique_ptr<ID3D11Device>&			m_device;
	ID3D11VertexShader*						m_vertexShader;
	ID3D11PixelShader*						m_pixelShader;
	ID3D11InputLayout*						m_layout;
	ShaderType								m_type;
};
