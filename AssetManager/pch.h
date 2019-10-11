#ifndef PCH_H
#define PCH_H

#define NOMINMAX
#ifdef _DEBUG
#define SPDLOG_ACTIVE_LEVEL 0
#endif // _DEBUG

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <filesystem>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>

#include <General/Math/Math.h>

#include <EngineDefines.h>

#include <Directx11/DX11Includes.h>

namespace fs = std::filesystem;

#endif //PCH_H
