#include "stdafx.h"
#include "Material.h"
#include "IShader.h"
#include "ITexture.h"
#include "ISamplerState.h"

Material::Material(const ShaderPtr& vertexShader, const ShaderPtr& pixelShader)
	: m_vertexShader(vertexShader)
	, m_pixelShader(pixelShader)
{
}

Material::~Material()
{
	m_vertexShader.reset();
	m_pixelShader.reset();
}

void Material::Render()
{
	if (m_diffuseTexture)
	{
		m_diffuseTexture->Bind();
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
