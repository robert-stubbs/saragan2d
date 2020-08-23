#ifndef _INPUT_H_
#define _INPUT_H_

#include "InputPlatform.h"
#include "Types.h"

namespace GameEngine
{
	class Input
	{
		private:
			InputPlatform* _platform;

			static Input _Instance;

			Input() {};
		public:
			void SetPlatform(PLATFORM platform);

			inline virtual bool IsKeyPressed(int key) { return _platform->IsKeyPressed(key); };
			inline virtual bool IsKeyReleased(int key) { return !IsKeyPressed(key); }

			inline virtual bool IsMouseButtonPressed(int button) { return _platform->IsMouseButtonPressed(button); };
			inline virtual bool IsMouseButtonReleased(int button) { return !IsMouseButtonPressed(button); }

			inline virtual float GetMouseX() { auto [x, y] = GetMousePos(); return x; }
			inline virtual float GetMouseY() { auto [x, y] = GetMousePos(); return y; }
			inline virtual std::pair<float, float> GetMousePos() { return _platform->GetMousePos(); };

			inline virtual int GetKey(int keycode) { return _platform->GetKey(keycode); };
			inline virtual int GetPlatformKey(int keycode) { return _platform->GetPlatformKey(keycode); };


			static Input& Get() {
				return _Instance;
			}
	};
}

#endif