#pragma once
namespace Logger
{
	void Log(const char* format, ...);
}

#define LOG(fmt,...) Logger::Log((fmt),__FILE__,__LINE__,__VA_ARGS__)