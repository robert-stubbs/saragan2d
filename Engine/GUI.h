#ifndef _GUI_H_
#define _GUI_H_

#include "GUIPlatform.h"
#include "Types.h"
#include "Layer.h"

namespace GameEngine
{
	class GUI : public Layer<GUIPlatform>
	{
	private:
		static GUI* _gui;

	public:
		GUI();
		GUI(RenderEngines EngineType);
		virtual void SetPlatform(PLATFORM platform) {};

		static GUI& GetGUI() {
			return *_gui;
		}

		static inline GUIPlatform& Get() { return *GetGUI()._instance; }
	};
}

#endif