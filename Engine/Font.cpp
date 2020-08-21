#include "EnginePCH.h"
#include "Font.h"
namespace GameEngine
{
	//https://pastebin.com/1jtDRvAf
	Font::Font(float fontSize, std::string filename)
	{
		font = 0;
		atlas = texture_atlas_new(512, 512, 1);
		font = texture_font_new_from_file(atlas, fontSize, filename.c_str());

		texture_glyph_t* g = texture_font_get_glyph(font, "A");
	}

	Font::~Font()
	{
		texture_font_delete(font);
		glDeleteTextures(1, &atlas->id);
		atlas->id = 0;
		texture_atlas_delete(atlas);
	}

}