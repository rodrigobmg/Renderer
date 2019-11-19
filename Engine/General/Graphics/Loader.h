#pragma once
#include "IVertexArray.h"
#include "IIndexArray.h"

class IGraphics;
namespace Loader
{
	ScenePtr LoadScene(const string& path, const IGraphicsPtr& graphics);
	SceneNodePtr LoadSceneNode(const string& path, const IGraphicsPtr& graphics);
}