#pragma once

class IShader;

class Material
{
public:
	Material(const ShaderPtr& vertexShader, const ShaderPtr& pixelShader);
	Material(const Material&) = delete;
	~Material();

	void SetVertexShader(const ShaderPtr& shader) { m_vertexShader = shader; }
	void SetPixelShader(const ShaderPtr& shader) { m_pixelShader = shader; }
	void SetDiffuseTexture(const TexturePtr& texture) { m_diffuseTexture = texture; }
	void SetSamplerState(const SamplerStatePtr& samplerState) { m_samplerState = samplerState; }

	void Render();

private:
	ShaderPtr		m_vertexShader;
	ShaderPtr		m_pixelShader;
	TexturePtr		m_diffuseTexture;
	SamplerStatePtr	m_samplerState;

};