#include "pch.h"
#include "ShaderCompiler.h"

#include <General/Application/Window.h>
#include <Directx11/Graphics/DX11Graphics.h>

static const fs::path kShaderExt(".hlsl");
static const fs::path kVertexShaderPostFix("_vs");
static const fs::path kPixelShaderPostFix("_ps");
static const string kWindowName("Shader Compiler Window");
static const int kWindowWidth = 1;
static const int kWindowHeight = 1;
static const float kScreenDepth = 1000.0f;
static const float kScreenNear = 0.1f;

void GetShaderFilePaths(const fs::path& inputPath, vector<fs::path>& shaderPaths)
{
	for (const auto& entry : fs::directory_iterator(inputPath))
	{
		if (entry.is_directory())
		{
			GetShaderFilePaths(entry.path(), shaderPaths);
		}
		else
		{
			fs::path path = entry.path();
			string ext = path.extension().string();
			if (path.extension() == kShaderExt || path.extension() == kShaderExt)
			{
				shaderPaths.push_back(path);
			}
		}
	}
}

bool ShaderCompiler::CompileShaders(const fs::path& inputPath)
{
	try
	{
		vector<fs::path> shaderPaths;
		GetShaderFilePaths(inputPath, shaderPaths);
		if (!shaderPaths.empty())
		{
			IGraphicsPtr graphics(new DX11Graphics());
			if (!graphics->Initialize(nullptr, kWindowWidth, kWindowHeight, true, false, kScreenDepth, kScreenNear))
			{
				if (graphics)
				{
					graphics->Shutdown();
				}
				ERROR_LOG("Failed to initialize graphics");
				return false;
			}

			for (const fs::path& path : shaderPaths)
			{
				ShaderType shaderType;
				if (path.string().find(kVertexShaderPostFix.string()) != string::npos)
				{
					shaderType = ShaderType::VERTEX_SHADER;
				}
				else
				{
					shaderType = ShaderType::PIXEL_SHADER;
				}

				if (!graphics->CreateShader(path.string(), shaderType))
				{
					if (graphics)
					{
						graphics->Shutdown();
					}
					ERROR_LOG("Failed to compile shader {}", path.string());
					return false;
				}
			}

			if (graphics)
			{
				graphics->Shutdown();
			}
		}
	}
	catch (const std::exception & ex)
	{
		ERROR_LOG("Error processing files {}", ex.what());
		return false;
	}

	return true;
}
