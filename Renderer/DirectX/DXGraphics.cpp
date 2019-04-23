#include "DXGraphics.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <stdlib.h>

DXGraphics::DXGraphics()
	:m_vsyncEnabled(false)
	,m_graphicsDeviceMemory(0)
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

bool GetGraphicsDeviceInfo(int screenWidth, int screenHeight, unsigned int& frameRateNumerator, unsigned int& frameRateDenominator, int& videoCardMemory, char* videoCardDescription)
{
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	unsigned int numModes;
	size_t stringLength;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	int error;

	// Create a DirectX graphics interface factory
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result))
	{
		return false;
	}

	// Use the factory to create an adapter for the primary graphics interface (video card)
	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))
	{
		return false;
	}

	// Enumerate the primary adapter output (monitor)
	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))
	{
		return false;
	}

	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor)
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Create a list to hold all the possible display modes for this monitor/video card combination
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
	{
		return false;
	}

	// Now fill the display mode list structures.
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(result))
	{
		return false;
	}

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	for (unsigned int i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == (unsigned int)screenWidth)
		{
			if (displayModeList[i].Height == (unsigned int)screenHeight)
			{
				frameRateNumerator = displayModeList[i].RefreshRate.Numerator;
				frameRateDenominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	// Get the adapter (video card) description
	result = adapter->GetDesc(&adapterDesc);
	if (FAILED(result))
	{
		return false;
	}

	// Store the dedicated video card memory in megabytes
	videoCardMemory = static_cast<int>(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// Convert the name of the video card to a character array and store it
	error = wcstombs_s(&stringLength, videoCardDescription, 128, &adapterDesc.Description[0], 128);
	if (error != 0)
	{
		return false;
	}

	// Release the display mode list.
	delete[] displayModeList;
	displayModeList = nullptr;

	// Release the adapter output.
	adapterOutput->Release();
	adapterOutput = nullptr;

	// Release the adapter.
	adapter->Release();
	adapter = nullptr;

	// Release the factory.
	factory->Release();
	factory = nullptr;

	return true;
}

bool DXGraphics::Initialize(int screenWidth, int screenHeight, bool vsync, const IWindow* window, bool fullscreen, float screenDepth, float screenNear)
{
	m_vsyncEnabled = vsync;
	//HRESULT result;
	unsigned int frameRateNumerator, frameRateDenominator;

	/*DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Texture2D* backBufferPtr;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterDesc;
	D3D11_VIEWPORT viewport;
	float fieldOfView, screenAspect;*/

	if (!GetGraphicsDeviceInfo(screenWidth, screenHeight, frameRateNumerator, frameRateDenominator, m_graphicsDeviceMemory, m_graphicsDeviceDescription))
	{
		return false;
	}

	return true;
}

void DXGraphics::Render()
{
}

void DXGraphics::Shutdown()
{
}
