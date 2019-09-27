#pragma once

#define NOMINMAX
#ifdef _DEBUG
#define SPDLOG_ACTIVE_LEVEL 0
#endif // _DEBUG

#include <string>
#include <vector>
#include <cstdint>
#include <cassert>
#include <stdlib.h>
#include <map>
#include <memory>
#include <climits>

#include <Externals/spdlog/spdlog.h>
#include <Externals/spdlog/sinks/msvc_sink.h>

#include <General/Math.h>

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
class Bitmap;
class ITexture;
class ISamplerState;

struct ObjectConstantBufferData;
struct VertexElement;
struct FrameConstantBufferData;
struct MaterialConstantBufferData;

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
typedef SharedPtr<Bitmap> BitmapPtr;
typedef SharedPtr<ITexture> TexturePtr;
typedef SharedPtr<ISamplerState> SamplerStatePtr;

#include <Directx11/DX11Includes.h>

#define ERROR_LOG(...) SPDLOG_ERROR(__VA_ARGS__)
#define DEBUG_LOG(...) SPDLOG_DEBUG(__VA_ARGS__)
