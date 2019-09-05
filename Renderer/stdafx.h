#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <d3d11.h>
#include <cassert>
#include <stdlib.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <map>

#include <General/Math.h>
#include <General/Logger.h>

template<typename T>
using SharedPtr = std::shared_ptr<T>;
template<typename T>
using UniquePtr = std::unique_ptr<T>;
template<typename T>
using vector = std::vector<T, std::allocator<T>>;
typedef std::string string;