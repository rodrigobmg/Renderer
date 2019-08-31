#include "DX11Graphics.h"

#include "DX11Mesh.h"
#include "DX11FrameConstantBuffer.h"
#include "DX11Shader.h"
#include "DX11ObjectConstantBuffer.h"

#include <General/IWindow.h>
#include <General/VertexArray.h>
#include <General/IndexArray.h>
#include <General/Object.h>
#include <General/Material.h>
#include <General/Camera.h>
#include <General/PointLight.h>

//Reference:http://www.rastertek.com/

DX11Graphics::DX11Graphics()
	:m_device(nullptr)
	,m_deviceContext(nullptr)
	,m_swapChain(nullptr)
	,m_renderTargetView(nullptr)
	,m_depthStencilBuffer(nullptr)
	,m_depthStencilState(nullptr)
	,m_depthStencilView(nullptr)
	,m_rasterState(nullptr)
	,m_camera(nullptr)
	,m_vsyncEnabled(false)
	,m_graphicsDeviceMemory(0)
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

void InitSwapChainDescription(DXGI_SWAP_CHAIN_DESC &swapChainDesc, int screenWidth, int screenHeight, bool vsyncEnabled, unsigned int refreshRateNumerator, unsigned int refreshRateDenominator, const IWindow * window, bool fullscreen)
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

bool DX11Graphics::Initialize(const IWindow* window, int screenWidth, int screenHeight, bool vsync, bool fullscreen, float screenDepth, float screenNear)
{
	m_vsyncEnabled = vsync;
	HRESULT result;
	unsigned int refreshRateNumerator, refreshRateDenominator;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;
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

	//Intialize swap chain description
	InitSwapChainDescription(swapChainDesc, screenWidth, screenHeight, m_vsyncEnabled, refreshRateNumerator, refreshRateDenominator, window, fullscreen);

	//Set the feature level  to DX11
	featureLevel = D3D_FEATURE_LEVEL_11_0;

	//Create the swap chain, D3D device and D3D device context
	{
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* deviceContext = nullptr;
		result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain,
			&device, NULL, &deviceContext);
		m_device.reset(device);
		m_deviceContext.reset(deviceContext);
	}

	if (FAILED(result))
	{
		return false;
	}

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

	// Create the camera object.
	m_camera = new Camera();
	if (!m_camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	Transform transform;
	transform.m_position = Vector3d(0.0f, 1.0f, -50.0f);
	m_camera->SetTransform(transform);

	m_frameConstantBuffer.reset(new DX11FrameConstantBuffer(m_device, m_deviceContext));
	m_frameConstantBufferData = new FrameConstantBufferData();

	//Create the projection matrix
	m_frameConstantBufferData->m_projection = Math::MatrixTranspose(Math::MatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth));

	//Create orthographic projection matrix
	m_orthoMatrix = Math::MatrixOrthographicLH(static_cast<float>(screenWidth), static_cast<float>(screenHeight), screenNear, screenDepth);

	m_pointLight = new PointLight(Color(1.0f), Vector3d(0.0f, 5.0f, -50.0f));

	return true;
}

static const float kClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
void DX11Graphics::Render()
{
	//Clear back buffer
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, kClearColor);

	//Clear depth buffer
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);


	// Get the view, and projection matrices and set them in the per frame constant buffer
	m_frameConstantBufferData->m_view = Math::MatrixTranspose(m_camera->GetViewMatrix());
	Color lightColor = m_pointLight->GetColor();
	Vector3d lightPosition = m_pointLight->GetPosition();
	m_frameConstantBufferData->m_pointLightData.m_color.x = lightColor.m_r;
	m_frameConstantBufferData->m_pointLightData.m_color.y = lightColor.m_g;
	m_frameConstantBufferData->m_pointLightData.m_color.z = lightColor.m_b;
	m_frameConstantBufferData->m_pointLightData.m_color.w = lightColor.m_a;
	m_frameConstantBufferData->m_pointLightData.m_position.x = lightPosition.x;
	m_frameConstantBufferData->m_pointLightData.m_position.y = lightPosition.y;
	m_frameConstantBufferData->m_pointLightData.m_position.z = lightPosition.z;
	m_frameConstantBufferData->m_pointLightData.m_position.w = 1.0f;

	m_frameConstantBuffer->SetData(m_frameConstantBufferData);

	for (SharedPtr<Core::Object>& object : m_objects)
	{
		object->Render();
	}

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
	// Release all the objects
	m_objects.clear();

	if (m_pointLight)
	{
		delete m_pointLight;
	}

	//Release constant buffer
	if (m_frameConstantBuffer)
	{
		m_frameConstantBuffer.reset();
	}

	if (m_frameConstantBufferData)
	{
		delete m_frameConstantBufferData;
	}

	// Release the camera object.
	if (m_camera)
	{
		delete m_camera;
		m_camera = nullptr;
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

SharedPtr<IVertexArray> DX11Graphics::CreateVertexArray(const vector<VertexFormat>& vertexData) const
{
	SharedPtr<IVertexArray> vertexArray(new VertexArray(vertexData.size(), vertexData.data()));
	return vertexArray;
}

SharedPtr<IIndexArray> DX11Graphics::CreateIndexArray(const vector<uint16_t>& indexData) const
{
	SharedPtr<IIndexArray> indexArray(new IndexArray(indexData.size(), indexData.data()));
	return indexArray;
}

SharedPtr<Core::Object> DX11Graphics::CreateObject()
{
	SharedPtr<Core::Object> newObject(new Core::Object());
	m_objects.push_back(newObject);
	return newObject;
}

SharedPtr<Core::Object> DX11Graphics::CreateObject(const string & meshPath, const string & vertexShaderPath, const string & pixelShaderPath)
{
	SharedPtr<IMesh> mesh(new DX11Mesh(m_device, m_deviceContext));
	if (mesh->Initialize(meshPath, *this))
	{
		SharedPtr<IShader> vertexShader(new DX11Shader(m_deviceContext, m_device, ShaderType::VERTEX_SHADER));
		if (vertexShader->Initialize(vertexShaderPath.c_str()))
		{
			SharedPtr<IShader> pixelShader(new DX11Shader(m_deviceContext, m_device, ShaderType::PIXEL_SHADER));
			if (pixelShader->Initialize(pixelShaderPath.c_str()))
			{
				SharedPtr<Core::Material> material(new Core::Material(vertexShader, pixelShader));
				SharedPtr<IConstantBuffer> objectConstantBuffer(new DX11ObjectConstantBuffer(m_device, m_deviceContext));
				SharedPtr<Core::Object> newObject(new Core::Object(mesh, material, objectConstantBuffer));
				m_objects.push_back(newObject);
				return newObject;
			}
		}
	}
	return nullptr;
}
