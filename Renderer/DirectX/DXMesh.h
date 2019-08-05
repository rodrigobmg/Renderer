#pragma once

#include <General/IMesh.h>
#include <d3d11.h>
#include <General/Pointers.h>

class DXMesh : public IMesh
{
public:
	DXMesh(const SmartPointer<ID3D11Device>& device, ID3D11DeviceContext* deviceContext);
	DXMesh(DXMesh& other);
	~DXMesh() {}

	virtual bool Initialize() override;
	virtual void Shutdown() override;
	virtual void Render() override;
	virtual int GetIndexCount() const  override { return m_indexCount; }

private:
	bool InitializeBuffers();
	void ShutdownBuffers();
	void RenderBuffers();

	SmartPointer<ID3D11Device>	m_device;
	ID3D11DeviceContext*		m_deviceContext;
	ID3D11Buffer*				m_vertexBuffer;
	ID3D11Buffer*				m_indexBuffer;
	int							m_vertexCount;
	int							m_indexCount;
};