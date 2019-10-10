#include "pch.h"
#include "Material.h"
#include "IShader.h"
#include "ITexture.h"
#include "ISamplerState.h"
#include "IConstantBuffer.h"
#include "MaterialConstantBuffer.h"

Material::Material(const IShaderPtr& vertexShader, const IShaderPtr& pixelShader, const IConstantBufferPtr& constantBuffer)
	: m_vertexShader(vertexShader)
	, m_pixelShader(pixelShader)
	, m_diffuse(nullptr)
	, m_specular(nullptr)
	, m_samplerState(nullptr)
	, m_materialConstantBuffer(constantBuffer)
	, m_materialConstantBufferData(new MaterialConstantBufferData())
{
}

Material::~Material()
{
	m_vertexShader.reset();
	m_pixelShader.reset();

	if (m_materialConstantBufferData)
	{
		delete m_materialConstantBufferData;
	}
}

void Material::SetShininess(float shininess)
{
	m_materialConstantBufferData->m_materialData.x = shininess;
}

void Material::SetShininessStrength(float shininessStrength)
{
	m_materialConstantBufferData->m_materialData.y = shininessStrength;
}

void Material::Render()
{
	if (m_materialConstantBuffer && m_materialConstantBufferData)
	{
		m_materialConstantBuffer->SetData(m_materialConstantBufferData);
	}

	if (m_diffuse)
	{
		m_diffuse->Bind(0);
	}

	if (m_specular)
	{
		m_specular->Bind(1);
	}

	if (m_vertexShader)
	{
		m_vertexShader->Render();
	}

	if (m_pixelShader)
	{
		m_pixelShader->Render();
	}

	if (m_samplerState)
	{
		m_samplerState->Bind();
	}
}
