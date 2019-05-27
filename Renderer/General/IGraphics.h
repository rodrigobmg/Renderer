#pragma once

class IWindow;
class IGraphics
{
public:
	virtual ~IGraphics() {};
	
	virtual bool Initialize(int screenWidth, int screenHeight, bool vsync, const IWindow* window, bool fullscreen, float screenDepth, float screenNear) = 0;
	virtual void Render(float r, float g, float b, float a) = 0;
	virtual void Shutdown() = 0;

protected:

};