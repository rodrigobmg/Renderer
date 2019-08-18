#pragma once
#include <memory>

class IShader;

namespace Core
{
	class Material
	{
	public:
		Material();
		Material(const Material&) = delete;
		Material(std::shared_ptr<IShader>& vertexShader, std::shared_ptr<IShader>& pixelShader);
		~Material();

		void SetVertexShader(std::shared_ptr<IShader>& shader) { m_vertexShader = shader; }
		void SetPixelShader(std::shared_ptr<IShader>& shader) { m_pixelShader = shader; }

		void Render();

	private:
		std::shared_ptr<IShader>	m_vertexShader;
		std::shared_ptr<IShader>	m_pixelShader;
	};
}