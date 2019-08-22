#include "Logger.h"

#include <Windows.h>
#include <stdio.h>
#pragma optimize("", off)
void Logger::Log(const char * format, ...)
{
	const size_t lenTemp = 256;
	char strTemp[lenTemp] = "DEBUG: %s %d ";
	strcat_s(strTemp, format);
	va_list args;
	va_start(args, format);
	const size_t deltaSize = 32;
	const size_t lenOutput = lenTemp + deltaSize;
	char strOutput[lenOutput];
	vsprintf_s(strOutput, lenOutput, strTemp, args);
	va_end(args);
	OutputDebugStringA(strOutput);
}
