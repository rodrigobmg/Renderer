#pragma once

#include "IShader.h"
#include "IVertexArray.h"

class IGraphics
{
public:
	virtual ~IGraphics() {};
	
	virtual bool Initialize(const WindowPtr& window, int screenWidth, int screenHeight, bool vsync, bool fullscreen, float screenDepth, float screenNear) = 0;
	virtual void StartRender() = 0;
	virtual void EndRender() = 0;
	virtual void Shutdown() = 0;
	virtual VertexArrayPtr CreateVertexArray(size_t vertexCount, const byte* vertexData, const vector<VertexElement>& vertexElements) const = 0;
	virtual IndexArrayPtr CreateIndexArray(const uint16_t* indexData, size_t indexCount) const = 0;
	virtual ShaderPtr CreateShader(const string& path, ShaderType shaderType) const = 0;
	virtual MeshPtr CreateMesh(const VertexArrayPtr& vertexData, const IndexArrayPtr& indexData, PrimitiveType primitive) const = 0;
	virtual ConstantBufferPtr CreateObjectConstantBuffer() const = 0;
	virtual TexturePtr CreateTexture(const BitmapPtr& bitmap) const = 0;
	virtual SamplerStatePtr CreateSamplerState() const = 0;
};