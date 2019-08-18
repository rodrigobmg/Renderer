#pragma once

#include <General/IMesh.h>
#include <string>
#include <d3d11.h>
#include <memory>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11Buffer;
class IVertexArray;
class IIndexArray;
class DXMesh : public IMesh
{
public:
	DXMesh(std::unique_ptr<ID3D11Device>& device, std::unique_ptr<ID3D11DeviceContext>& deviceContext);
	DXMesh(DXMesh& other) = delete;
	~DXMesh();

	virtual bool Initialize(const std::string& fileName, const IGraphics& graphics) override;
	virtual void Render() override;

private:
	bool InitializeBuffers();

	std::unique_ptr<ID3D11Device>&			m_device;
	std::unique_ptr<ID3D11DeviceContext>&	m_deviceContext;
	std::shared_ptr<IVertexArray>			m_vertices;
	std::shared_ptr<IIndexArray>			m_indices;
	ID3D11Buffer*							m_vertexBuffer;
	ID3D11Buffer*							m_indexBuffer;
	D3D_PRIMITIVE_TOPOLOGY					m_topology;
};