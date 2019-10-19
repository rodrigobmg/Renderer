#pragma once

class IShader;

class Material
{
public:
	Material(const IShaderPtr& vertexShader, const IShaderPtr& pixelShader, const IConstantBufferPtr& constantBuffer);
	Material(const Material&) = delete;
	~Material();

	void SetVertexShader(const IShaderPtr& shader) { m_vertexShader = shader; }
	void SetPixelShader(const IShaderPtr& shader) { m_pixelShader = shader; }
	void SetDiffuseTexture(const ITexturePtr& texture) { m_diffuse = texture; }
	void SetSamplerState(const ISamplerStatePtr& samplerState) { m_samplerState = samplerState; }
	void SetSpecularTexture(const ITexturePtr& texture) { m_specular = texture; }
	void SetShininess(float shininess);
	void SetShininessStrength(float shininessStrength);

	void Render();

private:
	IShaderPtr					m_vertexShader;
	IShaderPtr					m_pixelShader;
	ITexturePtr					m_diffuse;
	ITexturePtr					m_specular;
	ISamplerStatePtr			m_samplerState;
	IConstantBufferPtr			m_materialConstantBuffer;
	MaterialConstantBufferData* m_materialConstantBufferData;
};