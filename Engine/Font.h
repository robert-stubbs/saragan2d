#ifndef _FONT_H_
#define _FONT_H_

#include "FontPlatform.h"
#include "Types.h"
#include "Layer.h"

namespace GameEngine
{
	class Font : public Layer<FontPlatform>
	{
	private:
		static Font _font;

	public:
		Font();
		Font(RenderEngines EngineType);
		virtual void SetPlatform(PLATFORM platform) {};
		virtual ~Font();

		static Font& GetFont() {
			return _font;
		}

		static inline FontPlatform& Get() { return *GetFont()._instance; }
	};
}

#endif