#include "pch.h"
#include "Loader.h"

#include <General/Graphics/IGraphics.h>
#include <General/Graphics/VertexElement.h>
#include <General/Graphics/Scene.h>
#include <General/Graphics/SceneNode.h>
#include <General/Graphics/MeshNode.h>
#include <General/Graphics/Material.h>
#include <General/Math/Quaternion.h>
#include <General/Math/Vector4d.h>
#include <General/Math/Vector3d.h>
#include <General/Math/Vector2d.h>
#include <General/Math/Color.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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

void ExtractVertexData(const aiMesh* aiMesh, MeshData& meshData, const IGraphicsPtr& graphics)
{
	size_t vertexCount = aiMesh->mNumVertices;
	assert(vertexCount < std::numeric_limits<uint32_t>::max());
	size_t indexCount = static_cast<size_t>(aiMesh->mNumFaces) * static_cast<size_t>(aiMesh->mFaces[0].mNumIndices);
	UniquePtr<uint32_t> indexDataPtr(new uint32_t[indexCount]);
	uint32_t* indexData = indexDataPtr.get();

	assert(aiMesh->HasNormals());
	assert(aiMesh->HasPositions());
	vector<VertexElement> vertexElements(3);

	vertexElements[0].m_name = "POSITION";
	vertexElements[0].m_offset = 0;
	vertexElements[0].m_type = VertexElementType::FLOAT3;

	vertexElements[1].m_name = "NORMAL";
	vertexElements[1].m_offset = vertexElements[0].m_offset + VertexElement::GetVertexElementSize(vertexElements[0].m_type);
	vertexElements[1].m_type = VertexElementType::FLOAT3;

	vertexElements[2].m_name = "TEXCOORD";
	vertexElements[2].m_offset = vertexElements[1].m_offset + VertexElement::GetVertexElementSize(vertexElements[1].m_type);
	vertexElements[2].m_type = VertexElementType::FLOAT2;

	size_t stride = 0;
	for (int i = 0; i < vertexElements.size(); i++)
	{
		stride += VertexElement::GetVertexElementSize(vertexElements[i].m_type);
	}

	UniquePtr<byte> vertexDataPtr(new byte[vertexCount * stride]);
	byte* verteData = vertexDataPtr.get();
	for (size_t i = 0; i < vertexCount; i++)
	{
		//POSITION
		{ 
			memcpy((verteData + vertexElements[0].m_offset), &aiMesh->mVertices[i], VertexElement::GetVertexElementSize(vertexElements[0].m_type));
		}

		//NORMAL
		{
			memcpy((verteData + vertexElements[1].m_offset), &aiMesh->mNormals[i], VertexElement::GetVertexElementSize(vertexElements[1].m_type));
		}

		//TEXCOORD_0
		{
			Vector2d UV;
			if (aiMesh->HasTextureCoords(0))
			{
				UV.x = aiMesh->mTextureCoords[0][i].x;
				UV.y = aiMesh->mTextureCoords[0][i].y;
			}
			memcpy((verteData + vertexElements[2].m_offset), &UV, VertexElement::GetVertexElementSize(vertexElements[2].m_type));
		}

		verteData += stride;
	}

	for (unsigned int i = 0; i < aiMesh->mNumFaces; i++) {
		for (unsigned int j = 0; j < aiMesh->mFaces[i].mNumIndices; j++) {
			indexData[j + (i * 3)] = static_cast<uint32_t>(aiMesh->mFaces[i].mIndices[j]);
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

string GetTextureFilePathFromMaterial(const aiMaterial* material, const aiTextureType textureType, const string& directory) {

	bool result = false;
	aiString file;
	if (material->GetTexture(textureType, 0, &file) == aiReturn_SUCCESS)
	{
		string filePath(file.C_Str());
		filePath = filePath.substr(filePath.find_last_of("\\") + 1);
		filePath = directory + filePath;
		return filePath;
	}
	return string();
}

void ExtractMaterialData(const IGraphicsPtr& graphics, const aiScene* scene, const aiMesh* aiMesh, const std::string& directory, MaterialPtr& material)
{
	aiMaterial* aiMaterial = scene->mMaterials[aiMesh->mMaterialIndex];
	unsigned int diffuseCount = aiMaterial->GetTextureCount(aiTextureType_DIFFUSE);
	unsigned int specularCount = aiMaterial->GetTextureCount(aiTextureType_SPECULAR);
	unsigned int normalCount = aiMaterial->GetTextureCount(aiTextureType_HEIGHT);
	ITexturePtr diffuseTexture;
	ITexturePtr specularTexture;

	//Default diffuse
	{
		aiColor3D aiDiffuse;
		if (aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, aiDiffuse) == aiReturn_SUCCESS)
		{
			Color diffuseColor(aiDiffuse.r, aiDiffuse.g, aiDiffuse.b, 1.0f);
			diffuseTexture = graphics->CreateTexture(reinterpret_cast<float*>(&diffuseColor), 1, 1, sizeof(float) * 4, TextureFormat::RGBA32f);
		}
	}

	//Default specular
	{
		aiColor3D aiSpecular;
		if (aiMaterial->Get(AI_MATKEY_COLOR_SPECULAR, aiSpecular) == aiReturn_SUCCESS)
		{
			Color specularColor(aiSpecular.r, aiSpecular.g, aiSpecular.b, 1.0f);
			specularTexture = graphics->CreateTexture(reinterpret_cast<float*>(&specularColor), 1, 1, sizeof(float) * 4, TextureFormat::RGBA32f);
		}
	}

	string diffusePath;
	if (diffuseCount > 0)
	{
		diffusePath = GetTextureFilePathFromMaterial(aiMaterial, aiTextureType_DIFFUSE, directory);
	}

	string specularPath;
	if (specularCount > 0)
	{
		specularPath = GetTextureFilePathFromMaterial(aiMaterial, aiTextureType_SPECULAR, directory);
	}

	if (!diffusePath.empty())
	{
		diffuseTexture = graphics->CreateTexture(diffusePath);
	}
	if (!specularPath.empty())
	{
		specularTexture = graphics->CreateTexture(specularPath);
	}
	material->SetDiffuseTexture(diffuseTexture);
	material->SetSpecularTexture(specularTexture);

	float shininess = 0.0f;
	aiMaterial->Get(AI_MATKEY_SHININESS, shininess);
	material->SetShininess(shininess);

	float shininessStrength = 1.0f;
	aiMaterial->Get(AI_MATKEY_SHININESS_STRENGTH, shininessStrength);
	material->SetShininessStrength(shininessStrength);
}

SceneNodePtr CreateSceneDescription(const aiScene* scene, const aiNode* node, const string& directory, const IGraphicsPtr& graphics,
	const IShaderPtr& vertexShader, const IShaderPtr& pixelShader)
{
	vector<IMeshPtr> meshes;
	MaterialPtr defaultMaterial(new Material(vertexShader, pixelShader, graphics->CreateMaterialConstantBuffer()));
	vector<MaterialPtr> materials;

	for (unsigned int meshIndex = 0; meshIndex < node->mNumMeshes; meshIndex++)
	{
		MeshData meshData;
		const aiMesh* mesh = scene->mMeshes[node->mMeshes[meshIndex]];
		ExtractVertexData(mesh, meshData, graphics);

		MaterialPtr material = defaultMaterial;
		if (scene->HasMaterials())
		{
			material.reset(new Material(vertexShader, pixelShader, graphics->CreateMaterialConstantBuffer()));
			ExtractMaterialData(graphics, scene, mesh, directory, material);
			ISamplerStatePtr samplerState = graphics->CreateSamplerState();
			material->SetSamplerState(samplerState);
		}

		meshes.push_back(graphics->CreateMesh(meshData.m_vertexData, meshData.m_indexData, meshData.m_primitiveType));
		materials.push_back(material);
	}

	SceneNodePtr sceneNode;
	if (!meshes.empty())
	{
		MeshNode* meshNode = new MeshNode(meshes, materials, graphics->CreateObjectConstantBuffer(), node->mName.C_Str());
		sceneNode.reset(meshNode);
	}
	else
	{
		sceneNode.reset(new SceneNode(node->mName.C_Str()));
	}

	aiVector3D position, scale, rotation;
	node->mTransformation.Decompose(scale, rotation, position);
	sceneNode->m_localTransform.m_position = Vector3d(position.x, position.y, position.z);
	sceneNode->m_localTransform.m_scale = Vector3d(scale.x, scale.y, scale.z);
	sceneNode->m_localTransform.m_orientation = Quaternion(Vector3d(rotation.x, rotation.y, rotation.z));

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		SceneNodePtr child = CreateSceneDescription(scene, node->mChildren[i], directory, graphics, vertexShader, pixelShader);
		child->SetParent(sceneNode);
		sceneNode->AddChild(child);
	}

	return sceneNode;
}

ScenePtr Loader::LoadScene(const string& path, const IGraphicsPtr& graphics)
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

	IShaderPtr vertexShader = graphics->CreateShader(vertexShaderPath, ShaderType::VERTEX_SHADER);
	IShaderPtr pixelShader = graphics->CreateShader(pixelShaderPath, ShaderType::PIXEL_SHADER);

	Assimp::Importer importer; 
	const aiScene* aiScene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenNormals);
	if (!aiScene || aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !aiScene->mRootNode) {
		string error = importer.GetErrorString();
		ERROR_LOG("ERROR::ASSIMP:: {}", error);
		return false;
	}
	string directory = modelPath.substr(0, modelPath.find_last_of('/') + 1);
	ScenePtr scene(new Scene());
	SceneNodePtr rootNode = CreateSceneDescription(aiScene, aiScene->mRootNode, directory, graphics, vertexShader, pixelShader);
	scene->SetRootNode(rootNode);
	return scene;
}

SceneNodePtr Loader::LoadMeshNode(const string& path, const IGraphicsPtr& graphics)
{
	ScenePtr scene = LoadScene(path, graphics);
	return scene->GetRootNode();
}
