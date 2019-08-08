#pragma once

#include <General/IMesh.h>
#include <General/Pointers.h>
#include <string>
#include <d3d11.h>

class Texture;
class DXMesh : public IMesh
{
public:
	DXMesh(const SmartPointer<ID3D11Device>& device, ID3D11DeviceContext* deviceContext, const char* fileName);
	DXMesh(DXMesh& other);
	~DXMesh() {}

	virtual bool Initialize() override;
	virtual void Shutdown() override;
	virtual void Render() override;
	virtual int GetIndexCount() const  override { return m_indexCount; }

	ID3D11ShaderResourceView* GetTexture();

private:
	struct VertexType
	{
		Vector3d position;
		Vector2d uv;
	};

	bool InitializeBuffers();
	void ShutdownBuffers();
	void RenderBuffers();

	bool LoadTexture();
	void ReleaseTexture();

	SmartPointer<ID3D11Device>	m_device;
	ID3D11DeviceContext*		m_deviceContext;
	ID3D11Buffer*				m_vertexBuffer;
	ID3D11Buffer*				m_indexBuffer;
	Texture*					m_texture;
	std::string					m_textureFileName;
	int							m_vertexCount;
	int							m_indexCount;
};