#pragma once

#include <General/IGraphics.h>
#include <General/Matrix4d.h>

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

	virtual bool Initialize(const IWindow* window, int screenWidth, int screenHeight, bool vsync, bool fullscreen, float screenDepth, float screenNear) override;
	virtual void Render() override;
	virtual void Shutdown() override;

	virtual SharedPtr<IVertexArray> CreateVertexArray(const vector<VertexFormat>& vertexData) const override;
	virtual SharedPtr<IIndexArray> CreateIndexArray(const vector<uint16_t>& indexData) const override;
	virtual SharedPtr<Core::Object> CreateObject() override;
	virtual SharedPtr<Core::Object> CreateObject(const string& meshPath, const string& vertexShaderPath, const string& pixelShaderPath) override;

private:
	UniquePtr<ID3D11Device>			m_device;
	UniquePtr<ID3D11DeviceContext>	m_deviceContext;
	IDXGISwapChain*					m_swapChain;
	ID3D11RenderTargetView*			m_renderTargetView;
	ID3D11Texture2D*				m_depthStencilBuffer;
	ID3D11DepthStencilState*		m_depthStencilState;
	ID3D11DepthStencilView*			m_depthStencilView;
	ID3D11RasterizerState*			m_rasterState;
	ICamera*						m_camera;
	Matrix4d						m_projectionMatrix;
	Matrix4d						m_orthoMatrix;
	vector<SharedPtr<Core::Object>>	m_objects;
	SharedPtr<IConstantBuffer>		m_frameConstantBuffer;
	FrameConstantBufferData*		m_frameConstantBufferData;
	IPointLight*					m_pointLight;
	bool							m_vsyncEnabled;
	int								m_graphicsDeviceMemory;
	char							m_graphicsDeviceDescription[128];
};
