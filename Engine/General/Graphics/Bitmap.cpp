#include "pch.h"
#include "Bitmap.h"

#include <General/Math/Color.h>

Bitmap::Bitmap()
	: m_data(nullptr)
	, m_pitch(0)
	, m_width(0)
	, m_height(0)
	, m_channels(0)
	, m_dataFormat(Bitmap::DataFormat::FLOAT)
{
}

Bitmap::~Bitmap()
{
	if (m_data)
	{
		delete[] m_data;
	}
}

bool Bitmap::Alloc(const void* data, uint16_t width, uint16_t height, uint8_t channels, DataFormat dataFormat)
{
	if (m_data)
	{
		delete[] m_data;
	}

	m_dataFormat = dataFormat;

	size_t dataSize = 0;
	if (m_dataFormat == DataFormat::UNSIGNED_BYTE)
	{
		dataSize = sizeof(byte);
	}
	else
	{
		dataSize = sizeof(float);
	}

	m_pitch = dataSize * width * channels;
	size_t size = m_pitch * height;
	m_data = new byte[size];
	memcpy(m_data, data, size);
	assert(m_data);
	m_width = width;
	m_height = height;
	m_channels = channels;
	return true;
}
