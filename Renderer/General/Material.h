#pragma once

class IShader;

class Material
{
public:
	Material();
	Material(const Material&) = delete;
	Material(SharedPtr<IShader>& vertexShader, SharedPtr<IShader>& pixelShader);
	~Material();

	void SetVertexShader(SharedPtr<IShader>& shader) { m_vertexShader = shader; }
	void SetPixelShader(SharedPtr<IShader>& shader) { m_pixelShader = shader; }

	void Render();

private:
	SharedPtr<IShader>	m_vertexShader;
	SharedPtr<IShader>	m_pixelShader;
};