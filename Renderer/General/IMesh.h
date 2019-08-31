#pragma once

#include <General/IVertexArray.h>
#include <General/IIndexArray.h>

class IGraphics;
class IMesh
{
public:
	virtual ~IMesh() {};

	virtual bool Initialize(const string& fileName, const IGraphics& graphics) = 0;
	virtual void Render() = 0;
};