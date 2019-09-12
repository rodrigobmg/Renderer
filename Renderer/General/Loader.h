#pragma once
#include "IVertexArray.h"
#include "IIndexArray.h"

struct MeshData
{
	SharedPtr<IVertexArray>	m_vertexData;
	SharedPtr<IIndexArray>	m_indexData;
	PrimitiveType			m_primitiveType;
};

class IGraphics;
namespace Loader
{
	bool LoadModel(const string& path, MeshData& meshData, const IGraphics& graphics);
}