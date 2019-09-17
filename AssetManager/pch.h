#ifndef PCH_H
#define PCH_H

#ifdef _DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#else
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#endif

#define DEBUG_LOG SPDLOG_DEBUG
#define INFO_LOG SPDLOG_INFO
#define ERROR_LOG SPDLOG_ERROR

#include <iostream>
#include <filesystem>
#include <Externals/spdlog/spdlog.h>

#endif //PCH_H
