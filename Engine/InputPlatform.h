#ifndef _INPUT_PLATFORM_H_
#define _INPUT_PLATFORM_H_

namespace GameEngine
{
	class InputPlatform
	{
		public:
			InputPlatform() {};

			virtual bool IsKeyPressed(int key) = 0;
			inline virtual bool IsKeyReleased(int key) { return !IsKeyPressed(key); }

			virtual bool IsMouseButtonPressed(int button) = 0;
			virtual bool IsMouseButtonReleased(int button) { return !IsMouseButtonPressed(button); }

			inline virtual float GetMouseX() { auto [x, y] = GetMousePos(); return x; }
			inline virtual float GetMouseY() { auto [x, y] = GetMousePos(); return y; }
			virtual std::pair<float,float> GetMousePos() = 0;

			virtual int GetKey(int keycode) = 0;
	};
}

#endif