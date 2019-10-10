#pragma once

#include <General/Graphics/IVertexArray.h>
#include <General/Graphics/IIndexArray.h>

class IGraphics;
class IMesh
{
public:
	virtual ~IMesh() {};

	virtual bool Initialize() = 0;
	virtual void Render() = 0;
};