#include "EnginePCH.h"
#include "InputWindows.h"

#include "Engine.h"

namespace GameEngine
{
	InputWindows::InputWindows() : InputPlatform()
	{
		_key_codes = std::map<int, int>();

		_key_codes[ENGINE_KEY_SPACE]		= VK_SPACE;
		_key_codes[ENGINE_KEY_APOSTROPHE]	= VK_OEM_7;
		_key_codes[ENGINE_KEY_COMMA]		= VK_OEM_COMMA;
		_key_codes[ENGINE_KEY_MINUS]		= VK_OEM_MINUS;
		_key_codes[ENGINE_KEY_PERIOD]		= VK_OEM_PERIOD;
		_key_codes[ENGINE_KEY_SLASH]		= VK_OEM_4;
		_key_codes[ENGINE_KEY_0]			= 0x30;
		_key_codes[ENGINE_KEY_1]			= 0x31;
		_key_codes[ENGINE_KEY_2]			= 0x32;
		_key_codes[ENGINE_KEY_3]			= 0x33;
		_key_codes[ENGINE_KEY_4]			= 0x34;
		_key_codes[ENGINE_KEY_5]			= 0x35;
		_key_codes[ENGINE_KEY_6]			= 0x36;
		_key_codes[ENGINE_KEY_7]			= 0x37;
		_key_codes[ENGINE_KEY_8]			= 0x38;
		_key_codes[ENGINE_KEY_9]			= 0x39;
		_key_codes[ENGINE_KEY_SEMICOLON]	= VK_OEM_1;
		_key_codes[ENGINE_KEY_EQUAL]		= VK_OEM_PLUS;
		_key_codes[ENGINE_KEY_A]        	= 0x41;
		_key_codes[ENGINE_KEY_B]        	= 0x42;
		_key_codes[ENGINE_KEY_C]        	= 0x43;
		_key_codes[ENGINE_KEY_D]        	= 0x44;
		_key_codes[ENGINE_KEY_E]        	= 0x45;
		_key_codes[ENGINE_KEY_F]        	= 0x46;
		_key_codes[ENGINE_KEY_G]        	= 0x47;
		_key_codes[ENGINE_KEY_H]        	= 0x48;
		_key_codes[ENGINE_KEY_I]        	= 0x49;
		_key_codes[ENGINE_KEY_J]        	= 0x4A;
		_key_codes[ENGINE_KEY_K]        	= 0x4B;
		_key_codes[ENGINE_KEY_L]        	= 0x4C;
		_key_codes[ENGINE_KEY_M]        	= 0x4D;
		_key_codes[ENGINE_KEY_N]        	= 0x4E;
		_key_codes[ENGINE_KEY_O]        	= 0x4F;
		_key_codes[ENGINE_KEY_P]        	= 0x50;
		_key_codes[ENGINE_KEY_Q]        	= 0x51;
		_key_codes[ENGINE_KEY_R]        	= 0x52;
		_key_codes[ENGINE_KEY_S]        	= 0x53;
		_key_codes[ENGINE_KEY_T]        	= 0x54;
		_key_codes[ENGINE_KEY_U]        	= 0x55;
		_key_codes[ENGINE_KEY_V]        	= 0x56;
		_key_codes[ENGINE_KEY_W]        	= 0x57;
		_key_codes[ENGINE_KEY_X]        	= 0x58;
		_key_codes[ENGINE_KEY_Y]        	= 0x59;
		_key_codes[ENGINE_KEY_Z]            = 0x5A;
		_key_codes[ENGINE_KEY_LEFT_BRACKET] = VK_OEM_4;
		_key_codes[ENGINE_KEY_BACKSLASH]    = VK_OEM_5;
		_key_codes[ENGINE_KEY_RIGHT_BRACKET]= VK_OEM_6;
		_key_codes[ENGINE_KEY_GRAVE_ACCENT] = VK_OEM_3;
		_key_codes[ENGINE_KEY_WORLD_1]      = 0; // dunno
		_key_codes[ENGINE_KEY_WORLD_2]      = 0; // dunno

				/* Function keys */
		_key_codes[ENGINE_KEY_ESCAPE]       = VK_ESCAPE;
		_key_codes[ENGINE_KEY_ENTER]        = VK_RETURN;
		_key_codes[ENGINE_KEY_TAB]          = VK_TAB;
		_key_codes[ENGINE_KEY_BACKSPACE]    = VK_BACK;
		_key_codes[ENGINE_KEY_INSERT]       = VK_INSERT;
		_key_codes[ENGINE_KEY_DELETE]       = VK_DELETE;
		_key_codes[ENGINE_KEY_RIGHT]        = VK_RIGHT;
		_key_codes[ENGINE_KEY_LEFT]         = VK_LEFT;
		_key_codes[ENGINE_KEY_DOWN]         = VK_DOWN;
		_key_codes[ENGINE_KEY_UP]           = VK_UP;
		_key_codes[ENGINE_KEY_PAGE_UP]      = VK_PRIOR;
		_key_codes[ENGINE_KEY_PAGE_DOWN]    = VK_NEXT;
		_key_codes[ENGINE_KEY_HOME]         = VK_HOME;
		_key_codes[ENGINE_KEY_END]          = VK_END;
		_key_codes[ENGINE_KEY_CAPS_LOCK]    = VK_CAPITAL;
		_key_codes[ENGINE_KEY_SCROLL_LOCK]  = VK_SCROLL;
		_key_codes[ENGINE_KEY_NUM_LOCK]     = VK_NUMLOCK;
		_key_codes[ENGINE_KEY_PRINT_SCREEN] = VK_SNAPSHOT;
		_key_codes[ENGINE_KEY_PAUSE]        = VK_PAUSE;
		_key_codes[ENGINE_KEY_F1]           = VK_F1;
		_key_codes[ENGINE_KEY_F2]           = VK_F2;
		_key_codes[ENGINE_KEY_F3]           = VK_F3;
		_key_codes[ENGINE_KEY_F4]           = VK_F4;
		_key_codes[ENGINE_KEY_F5]           = VK_F5;
		_key_codes[ENGINE_KEY_F6]           = VK_F6;
		_key_codes[ENGINE_KEY_F7]           = VK_F7;
		_key_codes[ENGINE_KEY_F8]           = VK_F8;
		_key_codes[ENGINE_KEY_F9]           = VK_F9;
		_key_codes[ENGINE_KEY_F10]          = VK_F10;
		_key_codes[ENGINE_KEY_F11]          = VK_F11;
		_key_codes[ENGINE_KEY_F12]          = VK_F12;
		_key_codes[ENGINE_KEY_F13]          = VK_F13;
		_key_codes[ENGINE_KEY_F14]          = VK_F14;
		_key_codes[ENGINE_KEY_F15]          = VK_F15;
		_key_codes[ENGINE_KEY_F16]          = VK_F16;
		_key_codes[ENGINE_KEY_F17]          = VK_F17;
		_key_codes[ENGINE_KEY_F18]          = VK_F18;
		_key_codes[ENGINE_KEY_F19]          = VK_F19;
		_key_codes[ENGINE_KEY_F20]          = VK_F20;
		_key_codes[ENGINE_KEY_F21]          = VK_F21;
		_key_codes[ENGINE_KEY_F22]          = VK_F22;
		_key_codes[ENGINE_KEY_F23]          = VK_F23;
		_key_codes[ENGINE_KEY_F24]          = VK_F24;
		_key_codes[ENGINE_KEY_F25]          = 0; // Doesnt seem to exist
		_key_codes[ENGINE_KEY_KP_0]         = VK_NUMPAD0;
		_key_codes[ENGINE_KEY_KP_1]         = VK_NUMPAD1;
		_key_codes[ENGINE_KEY_KP_2]         = VK_NUMPAD2;
		_key_codes[ENGINE_KEY_KP_3]         = VK_NUMPAD3;
		_key_codes[ENGINE_KEY_KP_4]         = VK_NUMPAD4;
		_key_codes[ENGINE_KEY_KP_5]         = VK_NUMPAD5;
		_key_codes[ENGINE_KEY_KP_6]         = VK_NUMPAD6;
		_key_codes[ENGINE_KEY_KP_7]         = VK_NUMPAD7;
		_key_codes[ENGINE_KEY_KP_8]         = VK_NUMPAD8;
		_key_codes[ENGINE_KEY_KP_9]         = VK_NUMPAD9;
		_key_codes[ENGINE_KEY_KP_DECIMAL]   = VK_DECIMAL;
		_key_codes[ENGINE_KEY_KP_DIVIDE]    = VK_DIVIDE;
		_key_codes[ENGINE_KEY_KP_MULTIPLY]  = VK_MULTIPLY;
		_key_codes[ENGINE_KEY_KP_SUBTRACT]  = VK_SUBTRACT;
		_key_codes[ENGINE_KEY_KP_ADD]       = VK_ADD;
		_key_codes[ENGINE_KEY_KP_ENTER]     = VK_RETURN;
		_key_codes[ENGINE_KEY_KP_EQUAL]     = VK_OEM_PLUS;
		_key_codes[ENGINE_KEY_LEFT_SHIFT]   = VK_LSHIFT;
		_key_codes[ENGINE_KEY_LEFT_CONTROL] = VK_LCONTROL;
		_key_codes[ENGINE_KEY_LEFT_ALT]     = VK_LMENU;
		_key_codes[ENGINE_KEY_LEFT_SUPER]   = VK_LWIN;
		_key_codes[ENGINE_KEY_RIGHT_SHIFT]  = VK_RSHIFT;
		_key_codes[ENGINE_KEY_RIGHT_CONTROL]= VK_RCONTROL;
		_key_codes[ENGINE_KEY_RIGHT_ALT]    = VK_RMENU;
		_key_codes[ENGINE_KEY_RIGHT_SUPER]  = VK_RWIN;
		_key_codes[ENGINE_KEY_MENU]         = VK_MENU;

		_key_codes[ENGINE_MOUSE_BUTTON_1]   = VK_LBUTTON;
		_key_codes[ENGINE_MOUSE_BUTTON_2]   = VK_RBUTTON;
		_key_codes[ENGINE_MOUSE_BUTTON_3]   = VK_MBUTTON;
		_key_codes[ENGINE_MOUSE_BUTTON_4]   = VK_XBUTTON1;
		_key_codes[ENGINE_MOUSE_BUTTON_5]   = VK_XBUTTON2;
		_key_codes[ENGINE_MOUSE_BUTTON_6]   = 0; //unsure
		_key_codes[ENGINE_MOUSE_BUTTON_7]   = 0; //unsure
		_key_codes[ENGINE_MOUSE_BUTTON_8]   = 0; //unsure
		_key_codes[ENGINE_MOUSE_BUTTON_LAST]   = ENGINE_MOUSE_BUTTON_8;
		_key_codes[ENGINE_MOUSE_BUTTON_LEFT]   = ENGINE_MOUSE_BUTTON_1;
		_key_codes[ENGINE_MOUSE_BUTTON_RIGHT]  = ENGINE_MOUSE_BUTTON_2;
		_key_codes[ENGINE_MOUSE_BUTTON_MIDDLE] = ENGINE_MOUSE_BUTTON_3;

		_platform_key_codes = std::map<int, int>();
		for (auto pair : _key_codes)
		{
			if (pair.second != 0) {
				_platform_key_codes[pair.second] = pair.first;
			}
		}
	}

	bool InputWindows::IsKeyPressed(int key)
	{
		return GetKeyState(GetKey(key)) < 0;
	}

	bool InputWindows::IsMouseButtonPressed(int button)
	{
		return false;
	}

	std::pair<float, float> InputWindows::GetMousePos()
	{
		POINT mouse;                        // Stores The X And Y Coords For The Current Mouse Position
		GetCursorPos(&mouse);                   // Gets The Current Cursor Coordinates (Mouse Coordinates)
		//ScreenToClient(hWnd, &mouse);


		return { (float)mouse.x, (float)mouse.y };
	}

	int InputWindows::GetKey(int keycode)
	{
		return _key_codes[keycode];
	}

	int InputWindows::GetPlatformKey(int keycode)
	{
		return _platform_key_codes[keycode];
	}
}