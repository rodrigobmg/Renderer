#ifndef PCH_H
#define PCH_H

#ifdef _DEBUG
#define SPDLOG_ACTIVE_LEVEL 0
#endif // _DEBUG

#include <iostream>
#include <filesystem>

#include <Externals/spdlog/spdlog.h>
#include <Externals/spdlog/sinks/msvc_sink.h>

#define ERROR_LOG(...) SPDLOG_ERROR(__VA_ARGS__)
#define DEBUG_LOG(...) SPDLOG_DEBUG(__VA_ARGS__)

#endif //PCH_H
