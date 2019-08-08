#pragma once
#include <General/Math/Math.h>
#include <d3d11.h>

class TextureShader
{
private:
	struct MatrixBufferType
	{
		Matrix4d world;
		Matrix4d view;
		Matrix4d projection;
	};

public:
	TextureShader();
	TextureShader(const TextureShader& textureShader);
	~TextureShader();

	bool Initialize(ID3D11Device* device, HWND wnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, Matrix4d worldMatrix, Matrix4d viewMatrix, Matrix4d projectionMatrix, ID3D11ShaderResourceView* texture);

private:
	bool InitializeShader(ID3D11Device* device, HWND wnd, const WCHAR* vsFilePath, const WCHAR* psFilePath);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob* error, HWND wnd, const WCHAR* shaderFilePath);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, Matrix4d worldMatrix, Matrix4d viewMatrix, Matrix4d projectionMatrix, ID3D11ShaderResourceView* texture);
	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

	ID3D11VertexShader*	m_vertexShader;
	ID3D11PixelShader*	m_pixelShader;
	ID3D11InputLayout*	m_layout;
	ID3D11Buffer*		m_matrixBuffer;
	ID3D11SamplerState*	m_sampleState;
};

