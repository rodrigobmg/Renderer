#pragma once

#include "General/IGraphics.h"

#include <DirectXMath.h>

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct ID3D11Texture2D;
struct ID3D11DepthStencilState;
struct ID3D11DepthStencilView;
struct ID3D11RasterizerState;
class DXGraphics : public IGraphics
{
public:
	DXGraphics();
	DXGraphics(const DXGraphics&) = delete;
	DXGraphics& operator=(const DXGraphics&) = delete;
	~DXGraphics();

	virtual bool Initialize(int screenWidth, int screenHeight, bool vsync, const IWindow* window, bool fullscreen, float screenDepth, float screenNear);
	virtual void Render(float r, float g, float b, float a);
	virtual void Shutdown();

private:
	bool						m_vsyncEnabled;
	int							m_graphicsDeviceMemory;
	char						m_graphicsDeviceDescription[128];
	IDXGISwapChain*				m_swapChain;
	ID3D11Device*				m_device;
	ID3D11DeviceContext*		m_deviceContext;
	ID3D11RenderTargetView*		m_renderTargetView;
	ID3D11Texture2D*			m_depthStencilBuffer;
	ID3D11DepthStencilState*	m_depthStencilState;
	ID3D11DepthStencilView*		m_depthStencilView;
	ID3D11RasterizerState*		m_rasterState;
	DirectX::XMMATRIX			m_projectionMatrix;
	DirectX::XMMATRIX			m_worldMatrix;
	DirectX::XMMATRIX			m_orthoMatrix;
};
