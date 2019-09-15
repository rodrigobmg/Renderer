#pragma once

class IShader;

class Material
{
public:
	Material(const ShaderPtr& vertexShader, const ShaderPtr& pixelShader);
	Material(const Material&) = delete;
	~Material();

	void SetVertexShader(SharedPtr<IShader>& shader) { m_vertexShader = shader; }
	void SetPixelShader(SharedPtr<IShader>& shader) { m_pixelShader = shader; }

	void Render();

private:
	ShaderPtr	m_vertexShader;
	ShaderPtr	m_pixelShader;
};