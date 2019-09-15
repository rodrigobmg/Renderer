#pragma once

class Bitmap
{
public:
	Bitmap();
	Bitmap(const Bitmap&) = delete;
	~Bitmap();

	bool Alloc(void* data, uint8_t width, uint8_t height, uint8_t channels);

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
	const void* GetData() const { return m_data; }

private:
	void*	m_data;
	uint8_t	m_width;
	uint8_t	m_height;
	uint8_t	m_channels;
};