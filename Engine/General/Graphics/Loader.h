#pragma once
#include "IVertexArray.h"
#include "IIndexArray.h"

class IGraphics;
namespace Loader
{
	ScenePtr LoadScene(const string& path, const IGraphicsPtr& graphics);
	SceneNodePtr LoadMeshNode(const string& path, const IGraphicsPtr& graphics);
}