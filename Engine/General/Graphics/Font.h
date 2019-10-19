#pragma once
#include <string>

#include <General/Math/Vector2d.h>

class Font
{
public:
	Font() {}
	~Font() {}

	bool Load(string filePath, IGraphics& graphics);

private:
	struct Character
	{
		ITexturePtr	m_texture;
		VectorInt2d	m_size;
		VectorInt2d	m_bearing;
		uint32_t	m_advance;
	};

	vector<Character>	m_characters;
};