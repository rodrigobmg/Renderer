#pragma once

namespace
{
	std::string Format(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
#ifndef _MSC_VER
		size_t size = std::snprintf(nullptr, 0, format, args) + 1; // Extra space for '\0'
		std::unique_ptr<char[]> buf(new char[size]);
		std::vsnprintf(buf.get(), size, format, args);
		return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
#else
		int size = _vscprintf(format, args);
		std::string result(++size, 0);
		vsnprintf_s((char*)result.data(), size, _TRUNCATE, format, args);
		result[result.size() - 1] = '\n';
		return result;
#endif
		va_end(args);
	}
}

#define DEBUG_LOG(fmt,...) OutputDebugString((Format((fmt),__VA_ARGS__)).c_str())