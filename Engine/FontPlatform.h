#ifndef _FONT_PLATFORM_H_
#define _FONT_PLATFORM_H_

#include "Types.h"

namespace GameEngine
{
	class FontPlatform
	{
	public:
		FontPlatform() {};

		virtual void LoadFont(std::string name, float size) = 0;

		virtual FontBuffer GetString(std::string s, float x, float y, glm::vec4 col) = 0;
		virtual void GenerateBuffer(FontBuffer& buffer) = 0;
		virtual void RenderBuffer(FontBuffer& buffer) = 0;
	};
}

#endif