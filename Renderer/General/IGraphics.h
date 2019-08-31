#pragma once

class IWindow;
class IVertexArray;
class IIndexArray;
struct VertexFormat;
namespace Core
{
	class Object;
}
class IGraphics
{
public:
	virtual ~IGraphics() {};
	
	virtual bool Initialize(int screenWidth, int screenHeight, bool vsync, const IWindow* window, bool fullscreen, float screenDepth, float screenNear) = 0;
	virtual void Render() = 0;
	virtual void Shutdown() = 0;
	virtual SharedPtr<IVertexArray> CreateVertexArray(const vector<VertexFormat>& vertexData) const = 0;
	virtual SharedPtr<IIndexArray> CreateIndexArray(const vector<uint16_t>& indexData) const = 0;
	virtual SharedPtr<Core::Object> CreateObject() = 0;
	virtual SharedPtr<Core::Object> CreateObject(const string& meshPath, const string& vertexShaderPath, const string& pixelShaderPath) = 0;
};