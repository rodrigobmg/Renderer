#pragma once

#include <memory>
#include <General/Math/Math.h>

class IMesh;
class Material;
class IConstantBuffer;
struct ObjectConstantBufferData;
namespace Core
{
	class Material;
	class Object
	{
	public:
		Object();
		Object(const Object&) = delete;
		Object(std::shared_ptr<IMesh>& mesh, std::shared_ptr<Material>& material, std::shared_ptr<IConstantBuffer>& objectConstantBuffer);
		~Object();

		void SetMesh(std::shared_ptr<IMesh>& mesh) { m_mesh = mesh; }
		void SetMaterial(std::shared_ptr<Material>& material) { m_material = material; }

		void Render();

	private:
		std::shared_ptr<IMesh>				m_mesh;
		std::shared_ptr<Material>			m_material;
		std::shared_ptr<IConstantBuffer>	m_objectConstantBuffer;
		ObjectConstantBufferData*			m_objectConstantBufferData;

	public:
		Transform							m_transform;
	};
}