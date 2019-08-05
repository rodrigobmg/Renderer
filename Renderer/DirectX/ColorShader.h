#pragma once
#include <d3d11.h>
#include <General\Math\Math.h>

class ColorShader
{
private:
	struct MatrixBufferType
	{
		Matrix4d world;
		Matrix4d view;
		Matrix4d projection;
	};

public:
	ColorShader();
	ColorShader(const ColorShader& colorShader);
	~ColorShader();
	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, Matrix4d, Matrix4d, Matrix4d);

private:
	bool InitializeShader(ID3D11Device*, HWND, const WCHAR*, const WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, const WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, Matrix4d, Matrix4d, Matrix4d);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
};