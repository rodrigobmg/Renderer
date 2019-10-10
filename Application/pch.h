#ifndef PCH_H
#define PCH_H

#define NOMINMAX
#ifdef _DEBUG
#define SPDLOG_ACTIVE_LEVEL 0
#endif // _DEBUG

#include <string>
#include <vector>
#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/msvc_sink.h>

#include <General/Math/Math.h>

#include <EngineDefines.h>

#include <Directx11/DX11Includes.h>

#endif //PCH_H
