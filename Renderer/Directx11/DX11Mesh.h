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
	DX11Mesh(std::unique_ptr<ID3D11Device>& device, std::unique_ptr<ID3D11DeviceContext>& deviceContext);
	DX11Mesh(DX11Mesh& other) = delete;
	~DX11Mesh();

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