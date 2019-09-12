#pragma once

class IWindow;
class IVertexArray;
class IIndexArray;
struct VertexElement;
class SceneObject;
class IGraphics
{
public:
	virtual ~IGraphics() {};
	
	virtual bool Initialize(const IWindow* window, int screenWidth, int screenHeight, bool vsync, bool fullscreen, float screenDepth, float screenNear) = 0;
	virtual void Render() = 0;
	virtual void Shutdown() = 0;
	virtual SharedPtr<IVertexArray> CreateVertexArray(size_t vertexCount, const byte* vertexData, const vector<VertexElement>& vertexElements) const = 0;
	virtual SharedPtr<IIndexArray> CreateIndexArray(const uint16_t* indexData, size_t indexCount) const = 0;
	virtual SharedPtr<SceneObject> CreateObject() = 0;
	virtual SharedPtr<SceneObject> CreateObject(const string& meshPath, const string& vertexShaderPath, const string& pixelShaderPath) = 0;
};