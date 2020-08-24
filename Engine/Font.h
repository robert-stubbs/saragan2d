#ifndef _FONT_H_
#define _FONT_H_

#include "InputPlatform.h"
#include "Types.h"
#include "Layer.h"

namespace GameEngine
{
	class Font : public Layer<InputPlatform>
	{
	private:
		static Font _font;

	public:
		virtual void SetPlatform(PLATFORM platform) override;

		static Font& GetFont() {
			return _font;
		}

		static inline InputPlatform& Get() { return GetFont().Get(); }
	};
}

#endif