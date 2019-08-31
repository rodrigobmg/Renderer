#pragma once

class Bitmap
{
public:
	Bitmap();
	Bitmap(const Bitmap&) = delete;
	~Bitmap();

	bool Alloc(byte* data, int width, int height);

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
	const byte* GetData() const { return m_data; }

private:
	int		m_width;
	int		m_height;
	byte*	m_data;
};