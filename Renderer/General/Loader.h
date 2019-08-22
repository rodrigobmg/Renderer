#pragma once
#include "IVertexArray.h"
#include "IIndexArray.h"

struct MeshData
{
	std::shared_ptr<IVertexArray>	m_vertexData;
	std::shared_ptr<IIndexArray>	m_indexData;
	PrimitiveType					m_primitiveType;
};

class IGraphics;
namespace Loader
{
	bool LoadMesh(const std::string& path, MeshData& meshData, const IGraphics& graphics);
}