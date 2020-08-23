#ifndef _INPUT_WINDOWS_H_
#define _INPUT_WINDOWS_H_

#include "InputPlatform.h"

namespace GameEngine
{
	class InputWindows : public InputPlatform
	{
		private:
			std::map<int, int> _key_codes;
			std::map<int, int> _platform_key_codes;

		public:
			InputWindows();

			virtual bool IsKeyPressed(int key);

			virtual bool IsMouseButtonPressed(int button);

			virtual std::pair<float, float> GetMousePos();

			virtual int GetKey(int keycode);
			virtual int GetPlatformKey(int keycode);
	};
}

#endif