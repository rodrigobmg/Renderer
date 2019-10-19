#pragma once

class Bitmap
{
public:
	enum class DataFormat : uint8_t
	{
		UNSIGNED_BYTE,
		FLOAT
	};

	Bitmap();
	Bitmap(const Bitmap&) = delete;
	~Bitmap();

	bool Alloc(const void* data, uint16_t width, uint16_t height, uint8_t channels, DataFormat dataFormat);

	uint16_t GetWidth() const { return m_width; }
	uint16_t GetHeight() const { return m_height; }
	uint8_t GetNumChannels() const{ return m_channels; }
	const void* GetData() const { return m_data; }
	size_t GetPitch() const { return m_pitch; }
	DataFormat GetDataFormat() const { return m_dataFormat; }

private:
	void*		m_data;
	size_t		m_pitch;
	uint16_t	m_width;
	uint16_t	m_height;
	uint8_t		m_channels;
	DataFormat	m_dataFormat;
};