#pragma once

#include <memory>
#include <vector>

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
	virtual std::shared_ptr<IVertexArray> CreateVertexArray(const std::vector<VertexFormat>& vertexData) const = 0;
	virtual std::shared_ptr<IIndexArray> CreateIndexArray(const std::vector<uint16_t>& indexData) const = 0;
	virtual std::shared_ptr<Core::Object> CreateObject() = 0;
	virtual std::shared_ptr<Core::Object> CreateObject(const std::string& meshPath, const std::string& vertexShaderPath, const std::string& pixelShaderPath) = 0;
};