#include "stdafx.h"
#include "Bitmap.h"

#include "Color.h"

Bitmap::Bitmap()
	: m_data(nullptr)
	, m_width(0)
	, m_height(0)
	, m_channels(0)
{
}

Bitmap::~Bitmap()
{
	if (m_data)
	{
		delete[] m_data;
	}
}

bool Bitmap::Alloc(const float* data, uint16_t width, uint16_t height, uint8_t channels)
{
	size_t size = sizeof(float) * width * height * channels;
	m_data = new byte[size];
	memcpy(m_data, data, size);
	assert(m_data);
	m_width = width;
	m_height = height;
	m_channels = channels;
	return true;
}
