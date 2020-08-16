#ifndef _FONT_H_
#define _FONT_H_

//https://github.com/rougier/freetype-gl/blob/master/INSTALL.md
//https://www.freetype.org/

class Font
{
public:

	Font() {};
	Font(float fontSize, std::string filename = "Assets/Font/Vera.ttf");
	~Font();

	//texture_font_t* font;
	//texture_atlas_t* atlas;
	std::string filename;

};

#endif

