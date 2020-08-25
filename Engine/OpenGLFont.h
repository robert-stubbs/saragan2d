#ifndef _OPENGL_FONT_H_
#define _OPENGL_FONT_H_

#include "Types.h"
#include "FontPlatform.h"

namespace GameEngine {
	class OpenGLFont : public FontPlatform
	{
		// TODO - implement unique ID's where i can remove old ones

		private:
			texture_font_t* font;
			texture_atlas_t* atlas;
			std::string filename;
		public:
			OpenGLFont();
			~OpenGLFont();

			void LoadFont(std::string name, float size);
			virtual FontBuffer GetString(std::string s, float x, float y, glm::vec4 col);
			virtual void GenerateBuffer(FontBuffer& buffer);
			virtual void RenderBuffer(FontBuffer& buffer);
	};
}

#endif