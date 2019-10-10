#pragma once
#include "IVertexArray.h"
#include "IIndexArray.h"

class IGraphics;
namespace Loader
{
	SceneObjectPtr LoadModel(const string& path, const IGraphicsPtr& graphics);
}