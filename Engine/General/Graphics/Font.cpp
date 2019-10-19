#include "pch.h"
#include "Font.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <General/Graphics/IGraphics.h>
#include <General/Graphics/Bitmap.h>

bool Font::Load(string filePath, IGraphics& graphics)
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		ERROR_LOG("Could not initialize FreeType library");
		return false;
	}

	FT_Face face;
	if (FT_New_Face(ft, filePath.c_str(), 0, &face))
	{
		ERROR_LOG("ERROR::FREETYPE: Failed to load font from file {}", filePath);
		return false;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	m_characters.clear();
	m_characters.resize(128);
	for (byte c = 0; c < 128; c++)
	{
		if (c == ' ')
		{
			//Skip space
			continue;
		}

		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			ERROR_LOG("Failed to load Glyph for character {}", static_cast<char>(c));
			continue;
		}

		BitmapPtr bitmap(new Bitmap);
		if (!bitmap->Alloc(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, 1, Bitmap::DataFormat::UNSIGNED_BYTE))
		{
			ERROR_LOG("Failed to create bitmap for character {}", static_cast<char>(c));
			continue;
		}
		ITexturePtr texture = graphics.CreateTexture(bitmap);
		if (texture)
		{
			Character character;
			character.m_texture = texture;
			character.m_size.x = face->glyph->bitmap.width;
			character.m_size.y = face->glyph->bitmap.rows;
			character.m_bearing.x = face->glyph->bitmap_left;
			character.m_bearing.y = face->glyph->bitmap_top;
			character.m_advance = face->glyph->advance.x;
			m_characters[c] = character;
		}
		else
		{
			ERROR_LOG("Failed to create texture for character {}", static_cast<char>(c));
		}
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	return true;
}