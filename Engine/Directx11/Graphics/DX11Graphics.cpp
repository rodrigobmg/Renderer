#include "pch.h"
#include "DX11Graphics.h"

#include "DX11Mesh.h"
#include "DX11FrameConstantBuffer.h"
#include "DX11Shader.h"
#include "DX11ObjectConstantBuffer.h"
#include "DX11Texture.h"
#include "DX11SamplerState.h"
#include "DX11MaterialConstantBuffer.h"

#include <General/Application/IWindow.h>
#include <General/Graphics/VertexArray.h>
#include <General/Graphics/IndexArray.h>
#include <General/Graphics/Material.h>
#include <General/Graphics/Camera.h>
#include <General/Graphics/PointLight.h>
#include <General/Graphics/Font.h>
#include <General/Graphics/TextureManager.h>

//Reference:http://www.rastertek.com/

DX11Graphics::DX11Graphics()
	: m_device(nullptr)
	, m_deviceContext(nullptr)
	, m_swapChain(nullptr)
	, m_renderTargetView(nullptr)
	, m_depthStencilBuffer(nullptr)
	, m_depthStencilState(nullptr)
	, m_depthStencilView(nullptr)
	, m_rasterState(nullptr)
	, m_activeCamera(nullptr)
	, m_frameConstantBufferData(nullptr)
	, m_font(new Font())
	, m_textureManager(nullptr)
	, m_vsyncEnabled(false)
	, m_graphicsDeviceMemory(0)
	, m_graphicsDeviceDescription{0}
{
}

DX11Graphics::~DX11Graphics()
{
}

bool GetGraphicsDeviceInfo(int screenWidth, int screenHeight, unsigned int& refreshRateNumerator, unsigned int& refreshRateDenominator, int& videoCardMemory, char* videoCardDescription)
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
				refreshRateNumerator = displayModeList[i].RefreshRate.Numerator;
				refreshRateDenominator = displayModeList[i].RefreshRate.Denominator;
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

void InitSwapChainDescription(DXGI_SWAP_CHAIN_DESC &swapChainDesc, int screenWidth, int screenHeight, bool vsyncEnabled, unsigned int refreshRateNumerator, unsigned int refreshRateDenominator, const IWindowPtr& window, bool fullscreen)
{
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	//Set to a single back buffer
	swapChainDesc.BufferCount = 1;

	//Set the width and height of the back buffer
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;

	//Set regular 32-bit surface for the back buffer
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//Set refresh rate of back buffer
	if (vsyncEnabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = refreshRateNumerator;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = refreshRateDenominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 1;
	}

	// Set the usage of the back buffer.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	//Set the handle for the window to render to
	swapChainDesc.OutputWindow = window->GetHandle();

	//Turn multisampling off
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	//Set to full screen of windowed mode
	if (fullscreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	//Set the scan line ordering and scaling to unspecified
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//Discard the back buffer contents after presenting
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	//Don't set the advanced flags
	swapChainDesc.Flags = 0;
}

void InitDepthBufferDescription(D3D11_TEXTURE2D_DESC &depthBufferDesc, int screenWidth, int screenHeight)
{
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	//Set up the description of the depth buffer
	depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;
}

void InitDepthStencilDescription(D3D11_DEPTH_STENCIL_DESC &depthStencilDesc)
{
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	//Setup the desciption of the stencil state
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	//Stencil operations if the pixel is front-facing
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//Stencil operations if the pixel is back-facing
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
}

void InitDepthStencilViewDescription(D3D11_DEPTH_STENCIL_VIEW_DESC &depthStencilViewDesc)
{
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
}

void InitRasterDescription(D3D11_RASTERIZER_DESC &rasterDesc)
{
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;
}

bool DX11Graphics::Initialize(const IWindowPtr& window, int screenWidth, int screenHeight, bool vsync, bool fullscreen, float screenDepth, float screenNear)
{
	m_vsyncEnabled = vsync;
	//Set the feature level  to DX11
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_1;

	HRESULT result;
	unsigned int refreshRateNumerator, refreshRateDenominator;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ID3D11Texture2D* backBufferPtr;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterDesc;
	D3D11_VIEWPORT viewport;

	if (!GetGraphicsDeviceInfo(screenWidth, screenHeight, refreshRateNumerator, refreshRateDenominator, m_graphicsDeviceMemory, m_graphicsDeviceDescription))
	{
		return false;
	}

	//Create the swap chain, D3D device and D3D device context
	{
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* deviceContext = nullptr;

		UINT flags = 0;
#ifdef _DEBUG
		flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

		const D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;
		const UINT numFeatureLevels = 1;
		const UINT sdkVersion = D3D11_SDK_VERSION;

		if (window)
		{
			//Intialize swap chain description
			InitSwapChainDescription(swapChainDesc, screenWidth, screenHeight, m_vsyncEnabled, refreshRateNumerator, refreshRateDenominator, window, fullscreen);
			result = D3D11CreateDeviceAndSwapChain(NULL, driverType, NULL, flags, &featureLevel, numFeatureLevels, sdkVersion, &swapChainDesc, &m_swapChain,
				&device, NULL, &deviceContext);
		}
		else
		{
			result = D3D11CreateDevice(NULL, driverType, NULL, flags, &featureLevel, numFeatureLevels, sdkVersion, &device, NULL, &deviceContext);
		}

		m_device.reset(device);
		m_deviceContext.reset(deviceContext);
	}

	if (FAILED(result))
	{
		return false;
	}

	if (m_swapChain)
	{
		//Get the pointer to the back buffer
		result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
		if (FAILED(result))
		{
			return false;
		}

		//Create the render target view with the back buffer pointer
		result = m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView);
		if (FAILED(result))
		{
			return false;
		}

		//Release the pointer to the back buffer as we no longer need it
		backBufferPtr->Release();
		backBufferPtr = nullptr;

		//Initialize the description of the depth buffer
		InitDepthBufferDescription(depthBufferDesc, screenWidth, screenHeight);

		//Create the texture for the depth buffer using the filled out description
		result = m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
		if (FAILED(result))
		{
			return false;
		}

		//Initialize the description of the stencil state
		InitDepthStencilDescription(depthStencilDesc);

		//Create the depth stencil state
		result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
		if (FAILED(result))
		{
			return false;
		}

		//Set the depth stencil state
		m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

		// Initailze the depth stencil view.
		InitDepthStencilViewDescription(depthStencilViewDesc);

		// Create the depth stencil view.
		result = m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
		if (FAILED(result))
		{
			return false;
		}

		m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

		//Setup the raster description which will determine how and what polygons will be drawn
		InitRasterDescription(rasterDesc);

		//Create the rasterizer state from the description
		result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
		if (FAILED(result))
		{
			return false;
		}

		//Set the rasterizer state
		m_deviceContext->RSSetState(m_rasterState);

		//Set up viewport
		viewport.Width = static_cast<float>(screenWidth);
		viewport.Height = static_cast<float>(screenHeight);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		//Create the viewport
		m_deviceContext->RSSetViewports(1, &viewport);

		//Set up projection matrix
		float fieldOfView = Math::PI / 4.0f;
		float screenAspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);

		m_frameConstantBuffer.reset(new DX11FrameConstantBuffer(m_device, m_deviceContext));
		m_frameConstantBufferData = new FrameConstantBufferData();

		//Create the projection matrix
		m_frameConstantBufferData->m_projection = MatrixTranspose(MatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth));

		//Create orthographic projection matrix
		m_orthoMatrix = MatrixOrthographicLH(static_cast<float>(screenWidth), static_cast<float>(screenHeight), screenNear, screenDepth);
	}

	m_textureManager.reset(new TextureManager(*this));

	return true;
}

static const float kClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
void DX11Graphics::StartRender(const vector<PointLight*>& lights)
{
	//Clear back buffer
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, kClearColor);

	//Clear depth buffer
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);


	// Get the view, and projection matrices and set them in the per frame constant buffer
	m_frameConstantBufferData->m_view = MatrixTranspose(m_activeCamera->GetViewMatrix());

	m_frameConstantBufferData->m_pointLightData[0].m_color = lights[0]->GetColor();
	m_frameConstantBufferData->m_pointLightData[0].m_position = lights[0]->GetWorldPosition();
	m_frameConstantBufferData->m_pointLightData[0].m_intensity = lights[0]->GetIntensity();
	m_frameConstantBufferData->m_cameraPosition = m_activeCamera->GetTransform().m_position;

	m_frameConstantBuffer->SetData(m_frameConstantBufferData);
}

void DX11Graphics::EndRender()
{
	// Present the back buffer to the screen since rendering is complete.
	if (m_vsyncEnabled)
	{
		// Lock to screen refresh rate.
		m_swapChain->Present(1, 0);
	}
	else
	{
		// Present as fast as possible.
		m_swapChain->Present(0, 0);
	}
}

void DX11Graphics::Shutdown()
{
	m_textureManager.reset();
	m_font.reset();
	m_frameConstantBuffer.reset();

	if (m_frameConstantBufferData)
	{
		delete m_frameConstantBufferData;
	}

	// Before shutting down set to windowed mode or when you release the swap chain it will throw an exception.
	if (m_swapChain)
	{
		m_swapChain->SetFullscreenState(false, NULL);
	}

	if (m_rasterState)
	{
		m_rasterState->Release();
		m_rasterState = nullptr;
	}

	if (m_depthStencilView)
	{
		m_depthStencilView->Release();
		m_depthStencilView = nullptr;
	}

	if (m_depthStencilState)
	{
		m_depthStencilState->Release();
		m_depthStencilState = nullptr;
	}

	if (m_depthStencilBuffer)
	{
		m_depthStencilBuffer->Release();
		m_depthStencilBuffer = nullptr;
	}

	if (m_renderTargetView)
	{
		m_renderTargetView->Release();
		m_renderTargetView = nullptr;
	}

	if (m_deviceContext)
	{
		m_deviceContext->Release();
		m_deviceContext.release();
	}

	if (m_device)
	{
		m_device->Release();
		m_device.release();
	}

	if (m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = nullptr;
	}
}

SharedPtr<IVertexArray> DX11Graphics::CreateVertexArray(size_t vertexCount, const byte* vertexData, const vector<VertexElement>& vertexElements) const
{
	SharedPtr<IVertexArray> vertexArray(new VertexArray(vertexCount, vertexData, vertexElements));
	return vertexArray;
}

SharedPtr<IIndexArray> DX11Graphics::CreateIndexArray(const uint32_t* indexData, size_t indexCount) const
{
	SharedPtr<IIndexArray> indexArray(new IndexArray(indexCount, indexData));
	return indexArray;
}

IShaderPtr DX11Graphics::CreateShader(const string& path, ShaderType shaderType) const
{
	IShaderPtr shader(new DX11Shader(m_device, m_deviceContext, shaderType));
	if (shader->Initialize(path.c_str()))
	{
		return shader;
	}
	return nullptr;
}

IMeshPtr DX11Graphics::CreateMesh(const IVertexArrayPtr& vertexData, const IIndexArrayPtr& indexData, PrimitiveType primitive) const
{
	IMeshPtr mesh(new DX11Mesh(m_device, m_deviceContext, vertexData, indexData, primitive));
	if (mesh->Initialize())
	{
		return mesh;
	}
	return nullptr;
}

IConstantBufferPtr DX11Graphics::CreateObjectConstantBuffer() const
{
	return IConstantBufferPtr(new DX11ObjectConstantBuffer(m_device, m_deviceContext));
}

ITexturePtr DX11Graphics::CreateTexture(const void* data, UINT width, UINT height, UINT pitch, TextureFormat format) const
{
	ITexturePtr texture(new DX11Texture(m_device, m_deviceContext));
	if (texture->Initialize(data, width, height, pitch, format))
	{
		return texture;
	}
	return nullptr;
}

ITexturePtr DX11Graphics::CreateTexture(const string& path) const
{
	assert(m_textureManager);
	return m_textureManager->GetTexture(path);
}

ISamplerStatePtr DX11Graphics::CreateSamplerState() const
{
	ISamplerStatePtr samplerState(new DX11SamplerState(m_device, m_deviceContext));
	if (samplerState->Initialize())
	{
		return samplerState;
	}
	return nullptr;
}

IConstantBufferPtr DX11Graphics::CreateMaterialConstantBuffer() const
{
	return IConstantBufferPtr(new DX11MaterialConstantBuffer(m_device, m_deviceContext));
}

ICameraPtr DX11Graphics::CreateCamera() const
{
	ICameraPtr camera(new Camera());
	if (!m_activeCamera)
	{
		m_activeCamera = camera;
	}
	return camera;
}

bool DX11Graphics::LoadFont(const string& fontFile)
{
	assert(m_font);
	return m_font->Load(fontFile, *this);
}
