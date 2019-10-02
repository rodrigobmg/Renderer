#pragma once

#include <General/IMesh.h>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11Buffer;
class IVertexArray;
class IIndexArray;
class DX11Mesh : public IMesh
{
public:
	DX11Mesh(const UniquePtr<ID3D11Device>& device, const UniquePtr<ID3D11DeviceContext>& deviceContext, const IVertexArrayPtr& vertexArray, const IIndexArrayPtr& indexArray, PrimitiveType type);
	DX11Mesh(DX11Mesh& other) = delete;
	~DX11Mesh();

	virtual void Render() override;
	virtual bool Initialize() override;

private:
	const UniquePtr<ID3D11Device>&			m_device;
	const UniquePtr<ID3D11DeviceContext>&	m_deviceContext;
	IVertexArrayPtr							m_vertices;
	IIndexArrayPtr							m_indices;
	ID3D11Buffer*							m_vertexBuffer;
	ID3D11Buffer*							m_indexBuffer;
	D3D_PRIMITIVE_TOPOLOGY					m_topology;
};