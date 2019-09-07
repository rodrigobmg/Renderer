#include "Loader.h"
#include <Externals/TinyGLTF/Include.h>
#include <General/IGraphics.h>
#include <General/VertexElement.h>

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

		vector<VertexElement> vertexElements;
		vector<SharedPtr<byte>> vertexElementDataPtrs;
		size_t vertexCount = 0;
		for (auto iter = attributes.begin(); iter != attributes.end(); iter++)
		{
			VertexElement vertexElement;
			vertexElement.m_name = iter->first;
			int accessorIndex = iter->second;
			const Accessor& accessor = model.accessors[accessorIndex];
			assert(accessor.count < 65535);
			if (vertexCount == 0)
			{
				vertexCount = accessor.count;
			}
			else
			{
				assert(vertexCount == accessor.count);
			}

			switch (accessor.type)
			{
			case TINYGLTF_TYPE_SCALAR:
				vertexElement.m_type = VertexElementType::FLOAT1;
				break;
			case TINYGLTF_TYPE_VEC2:
				vertexElement.m_type = VertexElementType::FLOAT2;
				break;
			case TINYGLTF_TYPE_VEC3:
				vertexElement.m_type = VertexElementType::FLOAT3;
				break;
			case TINYGLTF_TYPE_VEC4:
				vertexElement.m_type = VertexElementType::FLOAT4;
				break;
			default:
				assert("Invalid accessor type");
				break;
			}
			vertexElement.m_offset = 0;
			if (!vertexElements.empty())
			{
				vertexElement.m_offset = vertexElements.back().m_offset + static_cast<uint16_t>(VertexElement::GetVertexElementSize(vertexElements.back().m_type));
			}
			vertexElements.push_back(vertexElement);

			size_t offset = accessor.byteOffset;
			int bufferViewIndex = accessor.bufferView;
			const BufferView bufferView = model.bufferViews[bufferViewIndex];
			int bufferIndex = bufferView.buffer;
			offset += bufferView.byteOffset;

			const Buffer& buffer = model.buffers[bufferIndex];
			const byte* bufferData = buffer.data.data();

			size_t stride = VertexElement::GetVertexElementSize(vertexElement.m_type);
			SharedPtr<byte> vertexElementDataPtr(new byte[stride * vertexCount]);
			byte* vertexElementData = vertexElementDataPtr.get();

			for (int i = 0; i < vertexCount; i++)
			{
				const byte* data = bufferData + offset + i * stride;
				memcpy(vertexElementData, data, stride);
				vertexElementData += stride;
			}

			vertexElementDataPtrs.push_back(vertexElementDataPtr);
		}

		assert(vertexElements.size() == vertexElementDataPtrs.size());

		size_t stride = 0;
		for (VertexElement& vertexElement : vertexElements)
		{
			stride += VertexElement::GetVertexElementSize(vertexElement.m_type);
		}
		size_t bufferSize = stride * vertexCount;
		UniquePtr<byte> vertexDataPtr(new byte[bufferSize]);
		byte* vertexData = vertexDataPtr.get();

		//Interweave data
		for (int i = 0; i < vertexCount; i++)
		{
			byte* destData = vertexData + stride * i;
			for (int j = 0; j < vertexElements.size(); j++)
			{
				size_t offset = vertexElements[j].m_offset;
				size_t elementSize = VertexElement::GetVertexElementSize(vertexElements[j].m_type);
				const byte* srcData = vertexElementDataPtrs[j].get() + elementSize * i;
				memcpy((destData + offset), srcData, elementSize);
			}
		}

		meshData.m_vertexData = graphics.CreateVertexArray(vertexCount, vertexDataPtr.get(), vertexElements);
	}

	return result;
}
