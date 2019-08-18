#include "Material.h"
#include "IShader.h"

Core::Material::Material()
	: m_vertexShader(nullptr)
	, m_pixelShader(nullptr)
{
}

Core::Material::Material(std::shared_ptr<IShader>& vertexShader, std::shared_ptr<IShader>& pixelShader)
	: m_vertexShader(vertexShader)
	, m_pixelShader(pixelShader)
{
}

Core::Material::~Material()
{
}

void Core::Material::Render()
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
