#pragma once

class Bitmap
{
public:
	Bitmap();
	Bitmap(const Bitmap&) = delete;
	~Bitmap();

	bool Alloc(const float* data, uint16_t width, uint16_t height, uint8_t channels);

	uint16_t GetWidth() const { return m_width; }
	uint16_t GetHeight() const { return m_height; }
	uint8_t GetNumChannels() const{ return m_channels; }
	const void* GetData() const { return m_data; }
	size_t GetPitch() const { return sizeof(float) * m_width * m_channels; }

private:
	void*		m_data;
	uint16_t	m_width;
	uint16_t	m_height;
	uint8_t		m_channels;
};