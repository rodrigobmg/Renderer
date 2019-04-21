#include "DXGraphics.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>

DXGraphics::DXGraphics()
	:m_vsyncEnabled(false)
	,m_videoCardMemory(0)
	,m_swapChain(nullptr)
	,m_device(nullptr)
	,m_deviceContext(nullptr)
	,m_renderTargetView(nullptr)
	,m_depthStencilBuffer(nullptr)
	,m_depthStencilState(nullptr)
	,m_depthStencilView(nullptr)
	,m_rasterState(nullptr)
{
}

DXGraphics::~DXGraphics()
{
}

bool DXGraphics::Initialize(int screenWidth, int screenHeight, bool vsync, const IWindow* window, bool fullscreen, float screenDepth, float screenNear)
{
	HRESULT result = 0;
	//IDXGIFactory* factory;
	//IDXGIAdapter* adapter;
	//IDXGIOutput* adapterOutput;
	//unsigned int numModes, i, numerator, denominator, stringLength;
	//DXGI_MODE_DESC* displayModeList;
	//DXGI_ADAPTER_DESC adapterDesc;
	//int error;
	//DXGI_SWAP_CHAIN_DESC swapChainDesc;
	//D3D_FEATURE_LEVEL featureLevel;
	//ID3D11Texture2D* backBufferPtr;
	//D3D11_TEXTURE2D_DESC depthBufferDesc;
	//D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	//D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	//D3D11_RASTERIZER_DESC rasterDesc;
	//D3D11_VIEWPORT viewport;
	//float fieldOfView, screenAspect;

	m_vsyncEnabled = vsync;


	return result;
}

void DXGraphics::Render()
{
}

void DXGraphics::Shutdown()
{
}
