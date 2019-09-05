#pragma once
#include <General/Transform.h>

class IMesh;
class Material;
class IConstantBuffer;
struct ObjectConstantBufferData;
class Material;
class SceneObject
{
public:
	SceneObject();
	SceneObject(const SceneObject&) = delete;
	SceneObject(SharedPtr<IMesh>& mesh, SharedPtr<Material>& material, SharedPtr<IConstantBuffer>& objectConstantBuffer);
	~SceneObject();

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