#pragma once

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
class Vector2d;
class Bitmap;
class ITexture;
class ISamplerState;
class ILight;
class Font;
class PointLight;

struct ObjectConstantBufferData;
struct VertexElement;
struct FrameConstantBufferData;
struct MaterialConstantBufferData;

typedef SharedPtr<SceneObject> SceneObjectPtr;
typedef WeakPtr<SceneObject> SceneObjectWeakPtr;
typedef SharedPtr<IMesh> IMeshPtr;
typedef SharedPtr<Material> MaterialPtr;
typedef SharedPtr<IConstantBuffer> IConstantBufferPtr;
typedef SharedPtr<IShader> IShaderPtr;
typedef SharedPtr<IVertexArray> IVertexArrayPtr;
typedef SharedPtr<IIndexArray> IIndexArrayPtr;
typedef SharedPtr<IWindow> IWindowPtr;
typedef SharedPtr<IGraphics> IGraphicsPtr;
typedef SharedPtr<Bitmap> BitmapPtr;
typedef SharedPtr<ITexture> ITexturePtr;
typedef SharedPtr<ISamplerState> ISamplerStatePtr;
typedef SharedPtr<ILight> ILightPtr;
typedef SharedPtr<ICamera> ICameraPtr;
typedef SharedPtr<IPointLight> IPointLightPtr;

#define ERROR_LOG(...) SPDLOG_ERROR(__VA_ARGS__)
#define DEBUG_LOG(...) SPDLOG_DEBUG(__VA_ARGS__)
#define INFO_LOG(...) SPDLOG_INFO(__VA_ARGS__)