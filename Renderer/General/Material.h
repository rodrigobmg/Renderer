#pragma once

class IShader;

class Material
{
public:
	Material(const ShaderPtr& vertexShader, const ShaderPtr& pixelShader, const ConstantBufferPtr& constantBuffer);
	Material(const Material&) = delete;
	~Material();

	void SetVertexShader(const ShaderPtr& shader) { m_vertexShader = shader; }
	void SetPixelShader(const ShaderPtr& shader) { m_pixelShader = shader; }
	void SetDiffuseTexture(const TexturePtr& texture) { m_diffuse = texture; }
	void SetSamplerState(const SamplerStatePtr& samplerState) { m_samplerState = samplerState; }
	void SetSpecularTexture(const TexturePtr& texture) { m_specular = texture; }
	void SetShininess(float shininess);
	void SetShininessStrength(float shininessStrength);

	void Render();

private:
	ShaderPtr					m_vertexShader;
	ShaderPtr					m_pixelShader;
	TexturePtr					m_diffuse;
	TexturePtr					m_specular;
	SamplerStatePtr				m_samplerState;
	ConstantBufferPtr			m_materialConstantBuffer;
	MaterialConstantBufferData* m_materialConstantBufferData;
};