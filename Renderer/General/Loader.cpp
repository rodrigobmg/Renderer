#include "Loader.h"
#include <Externals/TinyGLTF/Include.h>
#include <General/IGraphics.h>

bool Loader::LoadMesh(const string& path, MeshData& meshData, const IGraphics& graphics)
{
	using namespace tinygltf;

	assert(!path.empty());
	Object model;
	TinyGLTF loader;
	string err;
	string warn;

	bool result = loader.LoadBinaryFromFile(&model, &err, &warn, path);

	if (!warn.empty()) {
		printf("Warn: %s\n", warn.c_str());
	}

	if (!err.empty()) {
		printf("Error: %s\n", err.c_str());
	}

	if (result)
	{
		if (model.meshes.empty())
		{
			return false;
		}
		const Mesh& mesh = model.meshes[0];
		if (mesh.primitives.size() > 1)
		{
			printf("More than one primitive in %s", path.c_str());
		}
		const Primitive& primitive = mesh.primitives[0];

		switch (primitive.mode)
		{
		case 0:
			meshData.m_primitiveType = PrimitiveType::Points;
			break;
		case 1:
			meshData.m_primitiveType = PrimitiveType::Line;
			break;
		case 3:
			meshData.m_primitiveType = PrimitiveType::LineStrip;
			break;
		case 4:
			meshData.m_primitiveType = PrimitiveType::Triangles;
			break;
		case 5:
			meshData.m_primitiveType = PrimitiveType::TriangleStrip;
			break;
		default:
			printf("Unsupported primitive type %d", primitive.mode);
			return false;
		}

		int indicesAccessor = primitive.indices;
		std::map<string, int> attributes = primitive.attributes;
		int positionAccessor = -1;
		int colorAccessor = -1;
		int normalAccessor = -1;
		int uvAccessor = -1;
		for (auto iter = attributes.begin(); iter != attributes.end(); iter++)
		{
			if (iter->first == "POSITION")
			{
				positionAccessor = iter->second;
			}

			if (iter->first == "COLOR_0")
			{
				colorAccessor = iter->second;
			}

			if (iter->first == "NORMAL")
			{
				normalAccessor = iter->second;
			}

			if (iter->first == "TEXCOORD_0")
			{
				uvAccessor = iter->second;
			}
		}
		assert(positionAccessor > -1);
		assert(colorAccessor > -1);
		assert(normalAccessor > -1);
		assert(uvAccessor > -1);

		//Index
		{
			const Accessor& accessor = model.accessors[indicesAccessor];
			assert(accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT);
			size_t offset = accessor.byteOffset;
			int bufferViewIndex = accessor.bufferView;
			size_t count = accessor.count;

			const BufferView bufferView = model.bufferViews[bufferViewIndex];
			int bufferIndex = bufferView.buffer;
			offset += bufferView.byteOffset;

			const Buffer& buffer = model.buffers[bufferIndex];
			const unsigned char* data = buffer.data.data();

			size_t stride = sizeof(unsigned short);
			vector<uint16_t> indexData;
			for (int i = 0; i < count; i++)
			{
				const unsigned short* index = reinterpret_cast<const unsigned short*>(data + offset + i * stride);
				assert(index);
				indexData.push_back(*index);
			}
			meshData.m_indexData = graphics.CreateIndexArray(indexData);
		}

		vector<VertexFormat> vertexData;
		//Position
		{
			const Accessor& accessor = model.accessors[positionAccessor];
			assert(accessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
			assert(accessor.type == TINYGLTF_TYPE_VEC3);
			size_t offset = accessor.byteOffset;
			int bufferViewIndex = accessor.bufferView;
			size_t count = accessor.count;
			vertexData.resize(count);

			const BufferView bufferView = model.bufferViews[bufferViewIndex];
			int bufferIndex = bufferView.buffer;
			offset += bufferView.byteOffset;

			const Buffer& buffer = model.buffers[bufferIndex];
			const unsigned char* data = buffer.data.data();

			size_t stride = sizeof(float) * 3;
			for (int i = 0; i < count; i++)
			{
				const float* vectorPtr = reinterpret_cast<const float*>(data + offset + i * stride);
				assert(vectorPtr);
				vertexData[i].m_position = vectorPtr;
			}
		}

		//Color
		{
			const Accessor& accessor = model.accessors[colorAccessor];
			assert(accessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
			assert(accessor.type == TINYGLTF_TYPE_VEC4);
			size_t offset = accessor.byteOffset;
			int bufferViewIndex = accessor.bufferView;
			size_t count = accessor.count;

			const BufferView bufferView = model.bufferViews[bufferViewIndex];
			int bufferIndex = bufferView.buffer;
			offset += bufferView.byteOffset;

			const Buffer& buffer = model.buffers[bufferIndex];
			const unsigned char* data = buffer.data.data();

			size_t stride = sizeof(float) * 4;
			for (int i = 0; i < count; i++)
			{
				const float* vectorPtr = reinterpret_cast<const float*>(data + offset + i * stride);
				assert(vectorPtr);
				vertexData[i].m_color = vectorPtr;
			}
		}

		//Normal
		{
			const Accessor& accessor = model.accessors[normalAccessor];
			assert(accessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
			assert(accessor.type == TINYGLTF_TYPE_VEC3);
			size_t offset = accessor.byteOffset;
			int bufferViewIndex = accessor.bufferView;
			size_t count = accessor.count;

			const BufferView bufferView = model.bufferViews[bufferViewIndex];
			int bufferIndex = bufferView.buffer;
			offset += bufferView.byteOffset;

			const Buffer& buffer = model.buffers[bufferIndex];
			const unsigned char* data = buffer.data.data();

			size_t stride = sizeof(float) * 3;
			for (int i = 0; i < count; i++)
			{
				const float* vectorPtr = reinterpret_cast<const float*>(data + offset + i * stride);
				assert(vectorPtr);
				vertexData[i].m_normal = vectorPtr;
			}
		}

		//UV
		{
			const Accessor& accessor = model.accessors[uvAccessor];
			assert(accessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
			assert(accessor.type == TINYGLTF_TYPE_VEC2);
			size_t offset = accessor.byteOffset;
			int bufferViewIndex = accessor.bufferView;
			size_t count = accessor.count;

			const BufferView bufferView = model.bufferViews[bufferViewIndex];
			int bufferIndex = bufferView.buffer;
			offset += bufferView.byteOffset;

			const Buffer& buffer = model.buffers[bufferIndex];
			const unsigned char* data = buffer.data.data();

			size_t stride = sizeof(float) * 2;
			for (int i = 0; i < count; i++)
			{
				const float* vectorPtr = reinterpret_cast<const float*>(data + offset + i * stride);
				assert(vectorPtr);
				vertexData[i].m_texcoord0 = vectorPtr;
			}
		}

		meshData.m_vertexData = graphics.CreateVertexArray(vertexData);
	}

	return result;
}
