#pragma once

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
		Object(SharedPtr<IMesh>& mesh, SharedPtr<Material>& material, SharedPtr<IConstantBuffer>& objectConstantBuffer);
		~Object();

		void SetMesh(SharedPtr<IMesh>& mesh) { m_mesh = mesh; }
		void SetMaterial(SharedPtr<Material>& material) { m_material = material; }

		void Render();

	private:
		SharedPtr<IMesh>			m_mesh;
		SharedPtr<Material>			m_material;
		SharedPtr<IConstantBuffer>	m_objectConstantBuffer;
		ObjectConstantBufferData*	m_objectConstantBufferData;

	public:
		Transform					m_transform;
	};
}