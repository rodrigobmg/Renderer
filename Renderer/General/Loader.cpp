#include "stdafx.h"
#include "Loader.h"

#include <General/IGraphics.h>
#include <General/VertexElement.h>
#include <General/Vector4d.h>
#include <General/Vector3d.h>
#include <General/Vector2d.h>
#include <General/Bitmap.h>
#include <General/Color.h>
#include <General/SceneObject.h>
#include <General/Material.h>

#include <Externals/Assimp/include/assimp/Importer.hpp>
#include <Externals/Assimp/include/assimp/scene.h>
#include <Externals/Assimp/include/assimp/postprocess.h>
#include <Externals/STB_Image/Includes.h>

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

static const Vector4d kDefaultColor(0.0f);
struct MeshData
{
	MeshData()
		: m_vertexData(nullptr)
		, m_indexData(nullptr)
		, m_primitiveType(PrimitiveType::Point) {}

	SharedPtr<IVertexArray>	m_vertexData;
	SharedPtr<IIndexArray>	m_indexData;
	PrimitiveType			m_primitiveType;
};

void ExtractVertexData(const aiMesh* aiMesh, MeshData& meshData, const GraphicsPtr& graphics)
{
	size_t vertexCount = aiMesh->mNumVertices;
	assert(vertexCount < std::numeric_limits<uint16_t>::max());
	size_t indexCount = static_cast<size_t>(aiMesh->mNumFaces) * static_cast<size_t>(aiMesh->mFaces[0].mNumIndices);
	UniquePtr<uint16_t> indexDataPtr(new uint16_t[indexCount]);
	uint16_t* indexData = indexDataPtr.get();

	int numColorChannels = aiMesh->GetNumColorChannels();
	int numUVChannels = aiMesh->GetNumUVChannels();
	assert(numUVChannels > 0);

	size_t totalNumVertexElements = static_cast<size_t>((numColorChannels == 0 ? 1 : numColorChannels)) + static_cast<size_t>(numUVChannels);
	assert(aiMesh->HasNormals());
	totalNumVertexElements++;
	assert(aiMesh->HasPositions());
	totalNumVertexElements++;
	assert(totalNumVertexElements == 4);
	vector<VertexElement> vertexElements(totalNumVertexElements);

	vertexElements[0].m_name = "COLOR";
	vertexElements[0].m_offset = 0;
	vertexElements[0].m_type = VertexElementType::FLOAT4;

	vertexElements[1].m_name = "NORMAL";
	vertexElements[1].m_offset = vertexElements[0].m_offset + VertexElement::GetVertexElementSize(vertexElements[0].m_type);
	vertexElements[1].m_type = VertexElementType::FLOAT3;

	vertexElements[2].m_name = "POSITION";
	vertexElements[2].m_offset = vertexElements[1].m_offset + VertexElement::GetVertexElementSize(vertexElements[1].m_type);
	vertexElements[2].m_type = VertexElementType::FLOAT3;

	vertexElements[3].m_name = "TEXCOORD";
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

	meshData.m_indexData = graphics->CreateIndexArray(indexDataPtr.get(), indexCount);
	meshData.m_vertexData = graphics->CreateVertexArray(vertexCount, vertexDataPtr.get(), vertexElements);
}

static const int kRequiredNumberOfComponents = 4;
bool GetBitmapFromMaterial(const aiMaterial* material, const aiTextureType textureType, const string& directory, const BitmapPtr& bitmap) {

	bool result = false;
	aiString file;
	material->GetTexture(textureType, 0, &file);
	std::string filePath = std::string(file.C_Str());
	filePath = filePath.substr(filePath.find_last_of("\\") + 1);
	filePath = directory + filePath;

	int width, height, channels;
	float* data = stbi_loadf(filePath.c_str(), &width, &height, &channels, kRequiredNumberOfComponents);
	if (data)
	{
		result = bitmap->Alloc(data, width, height, kRequiredNumberOfComponents);
		if (!result)
		{
			ERROR_LOG("Failed to create bitmap: %s", filePath);
		}
	}
	else
	{
		ERROR_LOG("Failed to load texture: %s", filePath);
		return false;
	}
	stbi_image_free(data);

	return result;
}

void ExtractMaterialData(const GraphicsPtr& graphics, const aiScene* scene, const aiMesh* aiMesh, const std::string& directory, MaterialPtr& material)
{
	aiMaterial* aiMaterial = scene->mMaterials[aiMesh->mMaterialIndex];
	unsigned int diffuseCount = aiMaterial->GetTextureCount(aiTextureType_DIFFUSE);
	unsigned int specularCount = aiMaterial->GetTextureCount(aiTextureType_SPECULAR);
	unsigned int normalCount = aiMaterial->GetTextureCount(aiTextureType_HEIGHT);

	BitmapPtr diffuse(new Bitmap());

	aiColor3D aiDiffuse;
	aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, aiDiffuse);
	Color diffuseColor(aiDiffuse.r, aiDiffuse.g, aiDiffuse.b, 1.0f);
	diffuse->Alloc(reinterpret_cast<float*>(&diffuseColor), 1, 1, 4);

	if (diffuseCount > 0)
	{
		GetBitmapFromMaterial(aiMaterial, aiTextureType_DIFFUSE, directory, diffuse);
	}

	TexturePtr diffuseTexture = graphics->CreateTexture(diffuse);
	material->SetDiffuseTexture(diffuseTexture);
}

SceneObjectPtr CreateSceneObject(const aiScene* scene, const aiNode* node, const string& directory, const GraphicsPtr& graphics,
	const ShaderPtr& vertexShader, const ShaderPtr& pixelShader)
{
	SceneObjectPtr sceneObject(new SceneObject());
	vector<MeshPtr> meshes;
	MaterialPtr defaultMaterial(new Material(vertexShader, pixelShader));
	vector<MaterialPtr> materials;

	for (unsigned int meshIndex = 0; meshIndex < node->mNumMeshes; meshIndex++)
	{
		MeshData meshData;
		const aiMesh* mesh = scene->mMeshes[node->mMeshes[meshIndex]];
		ExtractVertexData(mesh, meshData, graphics);

		MaterialPtr material = defaultMaterial;
		if (scene->HasMaterials())
		{
			ExtractMaterialData(graphics, scene, mesh, directory, material);
			SamplerStatePtr samplerState = graphics->CreateSamplerState();
			material->SetSamplerState(samplerState);
		}

		meshes.push_back(graphics->CreateMesh(meshData.m_vertexData, meshData.m_indexData, meshData.m_primitiveType));
		materials.push_back(material);
	}

	if (!meshes.empty())
	{
		sceneObject->SetMeshData(meshes, materials, graphics->CreateObjectConstantBuffer());
	}

	aiVector3D position, scale, rotation;
	node->mTransformation.Decompose(scale, rotation, position);
	sceneObject->m_transform.m_position = Vector3d(position.x, position.y, position.z);
	sceneObject->m_transform.m_scale = Vector3d(scale.x, scale.y, scale.z);
	sceneObject->m_transform.m_rotation = Vector3d(rotation.x, rotation.y, rotation.z);

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		SceneObjectPtr child = CreateSceneObject(scene, node->mChildren[i], directory, graphics, vertexShader, pixelShader);
		child->SetParent(sceneObject);
		sceneObject->AddChild(child);
	}

	return sceneObject;
}

SceneObjectPtr Loader::LoadModel(const string& path, const GraphicsPtr& graphics)
{
	std::ifstream fileStream(path.c_str());
	if (!fileStream.is_open())
	{
		ERROR_LOG("Loader::LoadModel:: Cannot open file {}", path);
		return nullptr;
	}
	string fileDataString((std::istreambuf_iterator<char>(fileStream)),
		std::istreambuf_iterator<char>());

	json objectDescription = json::parse(fileDataString);
	string modelPath = objectDescription["model"];
	string vertexShaderPath = objectDescription["vertex_shader"];
	string pixelShaderPath = objectDescription["pixel_shader"];

	ShaderPtr vertexShader = graphics->CreateShader(vertexShaderPath, ShaderType::VERTEX_SHADER);
	ShaderPtr pixelShader = graphics->CreateShader(pixelShaderPath, ShaderType::PIXEL_SHADER);

	Assimp::Importer importer; 
	const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenNormals);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		string error = importer.GetErrorString();
		ERROR_LOG("ERROR::ASSIMP:: {}", error);
		return false;
	}
	string directory = modelPath.substr(0, modelPath.find_last_of('/') + 1);
	return CreateSceneObject(scene, scene->mRootNode, directory, graphics, vertexShader, pixelShader);
}
