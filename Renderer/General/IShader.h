#pragma once

enum class ShaderType
{
	VERTEX_SHADER = 0,
	PIXEL_SHADER
};

class IShader
{
public:
	virtual ~IShader() {}

	virtual bool Initialize(const char* shaderFilePath, const IVertexArrayPtr& vertexArray) = 0;
	virtual void Render() = 0;
};