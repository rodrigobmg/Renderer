#include "stdafx.h"
#include "Material.h"
#include "IShader.h"

Material::Material()
	: m_vertexShader(nullptr)
	, m_pixelShader(nullptr)
{
}

Material::Material(SharedPtr<IShader>& vertexShader, SharedPtr<IShader>& pixelShader)
	: m_vertexShader(vertexShader)
	, m_pixelShader(pixelShader)
{
}

Material::~Material()
{
}

void Material::Render()
{
	if (m_vertexShader)
	{
		m_vertexShader->Render();
	}

	if (m_pixelShader)
	{
		m_pixelShader->Render();
	}
}
