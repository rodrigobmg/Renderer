#include "DXShader.h"

#include <d3dcompiler.h>
#include <General/Logger.h>

DXShader::DXShader(std::unique_ptr<ID3D11DeviceContext>& deviceContext, std::unique_ptr<ID3D11Device>& device, ShaderType type)
	: m_deviceContext(deviceContext)
	, m_device(device)
	, m_vertexShader(nullptr)
	, m_type(type)
{
}

DXShader::~DXShader()
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

bool DXShader::Initialize(const char * shaderFilePath)
{
	ID3D10Blob* errorMessage;
	ID3D10Blob* shaderBuffer;

	using namespace std;
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
		Logger::Log("Invalid Shader Type");
		return false;
	}

	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, shaderFilePath, -1, wString, 4096);

	HRESULT result = D3DCompileFromFile(LPCWSTR(wString), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main",
		shaderTarget.c_str(), D3DCOMPILE_ENABLE_STRICTNESS, 0, &shaderBuffer, &errorMessage);

	if (FAILED(result))
	{
		if (errorMessage)
		{
			const char* compileErrors = (char*)(errorMessage->GetBufferPointer());
			Logger::Log("Error compiling shader %s", shaderFilePath);
			Logger::Log("%s", compileErrors);
		}
		else
		{
			Logger::Log("Missing Shader File");
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
		Logger::Log("Failed to create shader");
		return false;
	}

	if (m_type == ShaderType::VERTEX_SHADER)
	{
		D3D11_INPUT_ELEMENT_DESC inputElementDesc[3];
		inputElementDesc[0].SemanticName = "POSITION";
		inputElementDesc[0].SemanticIndex = 0;
		inputElementDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		inputElementDesc[0].InputSlot = 0;
		inputElementDesc[0].AlignedByteOffset = 0;
		inputElementDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputElementDesc[0].InstanceDataStepRate = 0;

		inputElementDesc[1].SemanticName = "COLOR";
		inputElementDesc[1].SemanticIndex = 0;
		inputElementDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		inputElementDesc[1].InputSlot = 0;
		inputElementDesc[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		inputElementDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputElementDesc[1].InstanceDataStepRate = 0;

		inputElementDesc[2].SemanticName = "NORMAL";
		inputElementDesc[2].SemanticIndex = 0;
		inputElementDesc[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		inputElementDesc[2].InputSlot = 0;
		inputElementDesc[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		inputElementDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputElementDesc[2].InstanceDataStepRate = 0;

		int numberOfElements = sizeof(inputElementDesc) / sizeof(inputElementDesc[0]);
		result = m_device->CreateInputLayout(inputElementDesc, numberOfElements, shaderBuffer->GetBufferPointer(),
			shaderBuffer->GetBufferSize(), &m_layout);

		if (FAILED(result))
		{
			Logger::Log("Failed to input layout");
			return false;
		}
	}

	return true;
}

void DXShader::Render()
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
