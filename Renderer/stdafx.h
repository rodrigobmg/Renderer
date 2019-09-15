#pragma once
#define NOMINMAX

#include <string>
#include <vector>
#include <cstdint>
#include <d3d11.h>
#include <cassert>
#include <stdlib.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <map>
#include <memory>
#include <climits>

#include <General/Math.h>
#include <General/Logger.h>

template<typename T>
using SharedPtr = std::shared_ptr<T>;
template<typename T>
using WeakPtr = std::weak_ptr<T>;
template<typename T>
using UniquePtr = std::unique_ptr<T>;
template<typename T>
using vector = std::vector<T, std::allocator<T>>;
typedef std::string string;

class IMesh;
class Material;
class IConstantBuffer;
class Material;
class SceneObject;
class IShader;
class IWindow;
class IVertexArray;
class IIndexArray;
class ICamera;
class IPointLight;
class IGraphics;
class Vector3d;

struct ObjectConstantBufferData;
struct VertexElement;
struct FrameConstantBufferData;

typedef SharedPtr<SceneObject> SceneObjectPtr;
typedef WeakPtr<SceneObject> SceneObjectWeakPtr;
typedef SharedPtr<IMesh> MeshPtr;
typedef SharedPtr<Material> MaterialPtr;
typedef SharedPtr<IConstantBuffer> ConstantBufferPtr;
typedef SharedPtr<IShader> ShaderPtr;
typedef SharedPtr<IVertexArray> VertexArrayPtr;
typedef SharedPtr<IIndexArray> IndexArrayPtr;
typedef SharedPtr<IWindow> WindowPtr;
typedef SharedPtr<IGraphics> GraphicsPtr;