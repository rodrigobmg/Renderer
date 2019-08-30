#pragma once

#include <General\IGraphics.h>

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct ID3D11Texture2D;
struct ID3D11DepthStencilState;
struct ID3D11DepthStencilView;
struct ID3D11RasterizerState;
class ICamera;
class IConstantBuffer;
struct FrameConstantBufferData;
class IPointLight;
class DX11Graphics : public IGraphics
{
public:
	DX11Graphics();
	DX11Graphics(const DX11Graphics&) = delete;
	DX11Graphics& operator=(const DX11Graphics&) = delete;
	~DX11Graphics();

	virtual bool Initialize(int screenWidth, int screenHeight, bool vsync, const IWindow* window, bool fullscreen, float screenDepth, float screenNear) override;
	virtual void Render() override;
	virtual void Shutdown() override;

	virtual std::shared_ptr<IVertexArray> CreateVertexArray(const std::vector<VertexFormat>& vertexData) const override;
	virtual std::shared_ptr<IIndexArray> CreateIndexArray(const std::vector<uint16_t>& indexData) const override;
	virtual std::shared_ptr<Core::Object> CreateObject() override;
	virtual std::shared_ptr<Core::Object> CreateObject(const std::string& meshPath, const std::string& vertexShaderPath, const std::string& pixelShaderPath) override;

private:
	std::unique_ptr<ID3D11Device>				m_device;
	std::unique_ptr<ID3D11DeviceContext>		m_deviceContext;
	IDXGISwapChain*								m_swapChain;
	ID3D11RenderTargetView*						m_renderTargetView;
	ID3D11Texture2D*							m_depthStencilBuffer;
	ID3D11DepthStencilState*					m_depthStencilState;
	ID3D11DepthStencilView*						m_depthStencilView;
	ID3D11RasterizerState*						m_rasterState;
	ICamera*									m_camera;
	Matrix4d									m_projectionMatrix;
	Matrix4d									m_orthoMatrix;
	std::vector<std::shared_ptr<Core::Object>>	m_objects;
	std::unique_ptr<IConstantBuffer>			m_frameConstantBuffer;
	FrameConstantBufferData*					m_frameConstantBufferData;
	IPointLight*								m_pointLight;
	bool										m_vsyncEnabled;
	int											m_graphicsDeviceMemory;
	char										m_graphicsDeviceDescription[128];
};
