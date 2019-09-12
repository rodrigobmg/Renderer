#include "stdafx.h"
#include "Loader.h"
#include <Externals/assimp/include/assimp/Importer.hpp>
#include <Externals/assimp/include/assimp/scene.h>
#include <Externals/assimp/include/assimp/postprocess.h>
#include <General/IGraphics.h>
#include <General/VertexElement.h>
#include <General/Vector4d.h>
#include <General/Vector3d.h>
#include <General/Vector2d.h>

static const Vector4d kDefaultColor(1.0f);

void GetMeshes(aiNode* node, const aiScene* scene, vector<aiMesh*>& o_meshes)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		o_meshes.push_back(scene->mMeshes[node->mMeshes[i]]);
	}

	for (unsigned int j = 0; j < node->mNumChildren; j++) {
		GetMeshes(node->mChildren[j], scene, o_meshes);
	}
}

void ExtractVertexData(aiMesh* aiMesh, MeshData& meshData, const IGraphics& graphics)
{
	size_t vertexCount = aiMesh->mNumVertices;
	size_t indexCount = aiMesh->mNumFaces * aiMesh->mFaces[0].mNumIndices;
	UniquePtr<uint16_t> indexDataPtr(new uint16_t[indexCount]);
	uint16_t* indexData = indexDataPtr.get();

	int numColorChannels = aiMesh->GetNumColorChannels();
	int numUVChannels = aiMesh->GetNumUVChannels();
	assert(numUVChannels > 0);

	size_t totalNumVertexElements = (numColorChannels == 0 ? 1 : numColorChannels) + numUVChannels;
	assert(aiMesh->HasNormals());
	totalNumVertexElements++;
	assert(aiMesh->HasPositions());
	totalNumVertexElements++;
	assert(totalNumVertexElements == 4);
	vector<VertexElement> vertexElements(totalNumVertexElements);

	vertexElements[0].m_name = "COLOR_0";
	vertexElements[0].m_offset = 0;
	vertexElements[0].m_type = VertexElementType::FLOAT4;

	vertexElements[1].m_name = "NORMAL";
	vertexElements[1].m_offset = vertexElements[0].m_offset + VertexElement::GetVertexElementSize(vertexElements[0].m_type);
	vertexElements[1].m_type = VertexElementType::FLOAT3;

	vertexElements[2].m_name = "POSITION";
	vertexElements[2].m_offset = vertexElements[1].m_offset + VertexElement::GetVertexElementSize(vertexElements[1].m_type);
	vertexElements[2].m_type = VertexElementType::FLOAT3;

	vertexElements[3].m_name = "TEXCOORD_0";
	vertexElements[3].m_offset = vertexElements[2].m_offset + VertexElement::GetVertexElementSize(vertexElements[2].m_type);
	vertexElements[3].m_type = VertexElementType::FLOAT2;

	size_t stride = 0;
	for (int i = 0; i < vertexElements.size(); i++)
	{
		stride += VertexElement::GetVertexElementSize(vertexElements[i].m_type);
	}

	float x = std::numeric_limits<float>::min();
	float y = std::numeric_limits<float>::min();
	float z = std::numeric_limits<float>::min();

	UniquePtr<byte> vertexDataPtr(new byte[vertexCount * stride]);
	byte* verteData = vertexDataPtr.get();
	for (size_t i = 0; i < vertexCount; i++)
	{
		//COLOR_0
		{
			if (numColorChannels > 0)
			{
				memcpy((verteData + vertexElements[0].m_offset), &aiMesh->mColors[0][i], VertexElement::GetVertexElementSize(vertexElements[0].m_type));
			}
			else
			{
				memcpy((verteData + vertexElements[0].m_offset), &kDefaultColor, VertexElement::GetVertexElementSize(vertexElements[0].m_type));
			}
		}

		//NORMAL
		{
			memcpy((verteData + vertexElements[1].m_offset), &aiMesh->mNormals[i], VertexElement::GetVertexElementSize(vertexElements[1].m_type));
		}

		//POSITION
		{
			x = std::max(x, aiMesh->mVertices[i].x);
			y = std::max(x, aiMesh->mVertices[i].y);
			z = std::max(x, aiMesh->mVertices[i].z);
			memcpy((verteData + vertexElements[2].m_offset), &aiMesh->mVertices[i], VertexElement::GetVertexElementSize(vertexElements[2].m_type));
		}

		//TEXCOORD_0
		{
			Vector2d UV(aiMesh->mTextureCoords[0][i].x, aiMesh->mTextureCoords[0][i].y);
			memcpy((verteData + vertexElements[3].m_offset), &UV, VertexElement::GetVertexElementSize(vertexElements[3].m_type));
		}

		verteData += stride;
	}

	uint16_t maxVal = 0;
	for (unsigned int i = 0; i < aiMesh->mNumFaces; i++) {
		for (unsigned int j = 0; j < aiMesh->mFaces[i].mNumIndices; j++) {
			indexData[j + (i * 3)] = aiMesh->mFaces[i].mIndices[j];
			maxVal = std::max(maxVal, indexData[j + (i * 3)]);
		}
	}

	switch (aiMesh->mPrimitiveTypes)
	{
	case aiPrimitiveType::aiPrimitiveType_LINE:
		meshData.m_primitiveType = PrimitiveType::Line;
		break;
	case aiPrimitiveType::aiPrimitiveType_POINT:
		meshData.m_primitiveType = PrimitiveType::Point;
		break;
	case aiPrimitiveType::aiPrimitiveType_TRIANGLE:
		meshData.m_primitiveType = PrimitiveType::Triangle;
		break;
	default:
		assert("Unknown primitive type");
		break;
	}

	meshData.m_indexData = graphics.CreateIndexArray(indexDataPtr.get(), indexCount);
	meshData.m_vertexData = graphics.CreateVertexArray(vertexCount, vertexDataPtr.get(), vertexElements);
}

bool Loader::LoadModel(const string& path, MeshData& meshData, const IGraphics& graphics)
{
	Assimp::Importer importer; 
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		string error = importer.GetErrorString();
		DEBUG_LOG("ERROR::ASSIMP:: %s", error);
		return false;
	}

	vector<aiMesh*> aiMeshes;
	GetMeshes(scene->mRootNode, scene, aiMeshes);

	ExtractVertexData(aiMeshes[0], meshData, graphics);

	return true;
}
