#include "stdafx.h"
#include "Bitmap.h"

#include "Color.h"

Bitmap::Bitmap()
	: m_width(0)
	, m_height(0)
	, m_data(nullptr)
{
}

Bitmap::~Bitmap()
{
	if (m_data)
	{
		delete[] m_data;
	}
}

bool Bitmap::Alloc(byte * data, int width, int height)
{
	memcpy(m_data, data, sizeof(Color) * width * height);
	m_width = width;
	m_height = height;
	return true;
}
