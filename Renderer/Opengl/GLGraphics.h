#pragma once

#include <General/IGraphics.h>

class GLGraphics : public IGraphics
{
public:
	GLGraphics() {}
	~GLGraphics() {};

	virtual bool Initialize(int screenWidth, int screenHeight, bool vsync, const IWindow* window, bool fullscreen, float screenDepth, float screenNear) override;
	virtual void Render(float r, float g, float b, float a) override;
	virtual void Shutdown() override;
};