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

bool Bitmap::Alloc(void* data, uint8_t width, uint8_t height, uint8_t channels)
{
	m_data = new byte[sizeof(float) * width * height * channels];
	memcpy(m_data, data, sizeof(float) * width * height * channels);
	assert(m_data);
	m_width = width;
	m_height = height;
	m_channels = channels;
	return true;
}
