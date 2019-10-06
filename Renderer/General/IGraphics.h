#pragma once

#include "IShader.h"
#include "IVertexArray.h"

class IGraphics
{
public:
	virtual ~IGraphics() {};
	
	virtual bool Initialize(const IWindowPtr& window, int screenWidth, int screenHeight, bool vsync, bool fullscreen, float screenDepth, float screenNear) = 0;
	virtual void StartRender(const vector<IPointLightPtr>& pointLights) = 0;
	virtual void EndRender() = 0;
	virtual void Shutdown() = 0;
	virtual IVertexArrayPtr CreateVertexArray(size_t vertexCount, const byte* vertexData, const vector<VertexElement>& vertexElements) const = 0;
	virtual IIndexArrayPtr CreateIndexArray(const uint16_t* indexData, size_t indexCount) const = 0;
	virtual IShaderPtr CreateShader(const string& path, ShaderType shaderType) const = 0;
	virtual IMeshPtr CreateMesh(const IVertexArrayPtr& vertexData, const IIndexArrayPtr& indexData, PrimitiveType primitive) const = 0;
	virtual IConstantBufferPtr CreateObjectConstantBuffer() const = 0;
	virtual IConstantBufferPtr CreateMaterialConstantBuffer() const = 0;
	virtual ITexturePtr CreateTexture(const BitmapPtr& bitmap) const = 0;
	virtual ISamplerStatePtr CreateSamplerState() const = 0;
	virtual ICameraPtr CreateCamera() const = 0;
	virtual void SetActiveCamera(const ICameraPtr& camera) = 0;
};