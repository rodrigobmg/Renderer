#pragma once

#include <General/Graphics/IGraphics.h>
#include <General/Math/Matrix4d.h>

class DX11Graphics : public IGraphics
{
public:
	DX11Graphics();
	DX11Graphics(const DX11Graphics&) = delete;
	DX11Graphics& operator=(const DX11Graphics&) = delete;
	~DX11Graphics();

	virtual bool Initialize(const IWindowPtr& window, int screenWidth, int screenHeight, bool vsync, bool fullscreen, float screenDepth, float screenNear) override;
	virtual void StartRender(const vector<IPointLightPtr>& pointLights) override;
	virtual void EndRender() override;
	virtual void Shutdown() override;

	virtual IVertexArrayPtr CreateVertexArray(size_t vertexCount, const byte* vertexData, const vector<VertexElement>& vertexElements) const override;
	virtual IIndexArrayPtr CreateIndexArray(const uint16_t* indexData, size_t indexCount) const override;
	virtual IShaderPtr CreateShader(const string& path, ShaderType shaderType) const override;
	virtual IMeshPtr CreateMesh(const IVertexArrayPtr& vertexData, const IIndexArrayPtr& indexData, PrimitiveType primitive) const override;
	virtual IConstantBufferPtr CreateObjectConstantBuffer() const override;
	virtual ITexturePtr CreateTexture(const BitmapPtr& bitmap) const override;
	virtual ISamplerStatePtr CreateSamplerState() const override;
	virtual IConstantBufferPtr CreateMaterialConstantBuffer() const override;
	virtual ICameraPtr CreateCamera() const override;
	virtual void SetActiveCamera(const ICameraPtr& camera) override { m_activeCamera = camera; }
	virtual bool LoadFont(const string& fontFile) override;

private:
	UniquePtr<ID3D11Device>			m_device;
	UniquePtr<ID3D11DeviceContext>	m_deviceContext;
	IDXGISwapChain*					m_swapChain;
	ID3D11RenderTargetView*			m_renderTargetView;
	ID3D11Texture2D*				m_depthStencilBuffer;
	ID3D11DepthStencilState*		m_depthStencilState;
	ID3D11DepthStencilView*			m_depthStencilView;
	ID3D11RasterizerState*			m_rasterState;
	mutable ICameraPtr				m_activeCamera;
	Matrix4d						m_projectionMatrix;
	Matrix4d						m_orthoMatrix;
	SharedPtr<IConstantBuffer>		m_frameConstantBuffer;
	FrameConstantBufferData*		m_frameConstantBufferData;
	UniquePtr<Font>					m_font;
	bool							m_vsyncEnabled;
	int								m_graphicsDeviceMemory;
	char							m_graphicsDeviceDescription[128];
};
