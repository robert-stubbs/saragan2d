#include "EnginePCH.h"

#include "cRegWnd.h"


cRegWnd::cRegWnd(HINSTANCE hInstance, WNDPROC WndProc, bool fullscreen, int width, int height)
{
	screen_fullscreen = fullscreen;
	screen_width = width;
	screen_height = height;
	hInst = hInstance;
	
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLASSNAME;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
}

void cRegWnd::Register()
{
	RegisterClassEx(&wc);
	
	if (screen_fullscreen)
	{

		DEVMODE dmScreenSettings;                   // Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));       // Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);       // Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = screen_width;            // Selected Screen Width
		dmScreenSettings.dmPelsHeight = screen_height;           // Selected Screen Height
		dmScreenSettings.dmBitsPerPel = 24;             // Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL, L"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", L"Saragan", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				screen_fullscreen = FALSE;
			}
			else {
				MessageBox(NULL, L"Program Will Now Close.", L"ERROR", MB_OK | MB_ICONSTOP);
				return;
			}
		}
	}
}
