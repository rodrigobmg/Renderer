#pragma once

class IWindow;
class IRenderer
{
public:
	virtual ~IRenderer() {}

	virtual bool Initialize(int screenWidth, int screenHeight, bool vsync, const IWindow* window, bool fullscreen, float screenDepth, float screenNear) = 0;
};