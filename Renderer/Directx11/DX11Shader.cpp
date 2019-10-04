#include "stdafx.h"
#include "DX11Shader.h"

#include <General\VertexArray.h>
#include <General\VertexElement.h>

#include <d3dcompiler.h>

static const char* kMainMethod = "main";
static const int kWCHARLength = 4096;

DX11Shader::DX11Shader(const UniquePtr<ID3D11Device>& device, const UniquePtr<ID3D11DeviceContext>& deviceContext, ShaderType type)
	: m_device(device)
	, m_deviceContext(deviceContext)
	, m_vertexShader(nullptr)
	, m_pixelShader(nullptr)
	, m_layout(nullptr)
	, m_type(type)
{
}

DX11Shader::~DX11Shader()
{
	if (m_layout)
	{
		m_layout->Release();
		m_layout = nullptr;
	}

	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = nullptr;
	}

	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = nullptr;
	}
}

bool DX11Shader::Initialize(const char * shaderFilePath, const IVertexArrayPtr& vertexArray)
{
	ID3D10Blob* errorMessage;
	ID3D10Blob* shaderBuffer;

	string shaderTarget;

	switch (m_type)
	{
	case ShaderType::VERTEX_SHADER:
		shaderTarget = "vs_5_0";
		break;
	case ShaderType::PIXEL_SHADER:
		shaderTarget = "ps_5_0";
		break;
	default:
		ERROR_LOG("Invalid Shader Type");
		return false;
	}

	SharedPtr<wchar_t> wString(new wchar_t[kWCHARLength]);
	MultiByteToWideChar(CP_ACP, 0, shaderFilePath, -1, wString.get(), kWCHARLength);

	UINT compileFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif // DEBUG_SHADERS


	HRESULT result = D3DCompileFromFile(LPCWSTR(wString.get()), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, kMainMethod,
		shaderTarget.c_str(), compileFlags, 0, &shaderBuffer, &errorMessage);

	if (FAILED(result))
	{
		if (errorMessage)
		{
			const char* compileErrors = (char*)(errorMessage->GetBufferPointer());
			ERROR_LOG("Error compiling shader {}", shaderFilePath);
			ERROR_LOG("Compiler Errors: {}", compileErrors);
		}
		else
		{
			ERROR_LOG("Missing Shader File");
		}
		return false;
	}

	if (m_type == ShaderType::VERTEX_SHADER)
	{
		result = m_device->CreateVertexShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	}
	else
	{
		result = m_device->CreatePixelShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	}

	if (FAILED(result))
	{
		ERROR_LOG("Failed to create shader");
		return false;
	}

	if (m_type == ShaderType::VERTEX_SHADER)
	{
		if (vertexArray)
		{
			const vector<VertexElement>& vertexElements = vertexArray->GetVertexElements();
			D3D11_INPUT_ELEMENT_DESC* inputElementDesc = new D3D11_INPUT_ELEMENT_DESC[vertexElements.size()];

			for (int i = 0; i < vertexElements.size(); i++)
			{
				inputElementDesc[i].SemanticName = vertexElements[i].m_name.c_str();
				inputElementDesc[i].SemanticIndex = vertexElements[i].m_index;

				switch (vertexElements[i].m_type)
				{
				case VertexElementType::FLOAT1:
					inputElementDesc[i].Format = DXGI_FORMAT_R32_FLOAT;
					break;
				case VertexElementType::FLOAT2:
					inputElementDesc[i].Format = DXGI_FORMAT_R32G32_FLOAT;
					break;
				case VertexElementType::FLOAT3:
					inputElementDesc[i].Format = DXGI_FORMAT_R32G32B32_FLOAT;
					break;
				case VertexElementType::FLOAT4:
					inputElementDesc[i].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
					break;
				default:
					ERROR_LOG("Invalid vertex type");
					return false;
				}
				inputElementDesc[i].InputSlot = 0;
				inputElementDesc[i].AlignedByteOffset = vertexElements[i].m_offset;
				inputElementDesc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				inputElementDesc[i].InstanceDataStepRate = 0;
			}

			UINT numberOfElements = static_cast<UINT>(vertexElements.size());
			result = m_device->CreateInputLayout(inputElementDesc, numberOfElements, shaderBuffer->GetBufferPointer(),
				shaderBuffer->GetBufferSize(), &m_layout);

			delete[] inputElementDesc;
		}
		else
		{
			D3D11_INPUT_ELEMENT_DESC inputElementDesc[3] =
			{
				{"POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0},
				{"NORMAL",		0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	12,	D3D11_INPUT_PER_VERTEX_DATA,	0},
				{"TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	24,	D3D11_INPUT_PER_VERTEX_DATA,	0}
			};
			int numberOfElements = sizeof(inputElementDesc) / sizeof(inputElementDesc[0]);
			result = m_device->CreateInputLayout(inputElementDesc, numberOfElements, shaderBuffer->GetBufferPointer(),
				shaderBuffer->GetBufferSize(), &m_layout);
		}

		if (FAILED(result))
		{
			ERROR_LOG("Failed to create input layout");
			return false;
		}
	}

	shaderBuffer->Release();
	shaderBuffer = nullptr;

	if (errorMessage)
	{
		errorMessage->Release();
		errorMessage = nullptr;
	}

	return true;
}

void DX11Shader::Render()
{
	if (m_type == ShaderType::VERTEX_SHADER)
	{
		m_deviceContext->IASetInputLayout(m_layout);
		m_deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	}
	else
	{
		m_deviceContext->PSSetShader(m_pixelShader, NULL, 0);
	}
}
