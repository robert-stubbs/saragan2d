#ifndef _CHILD_WINDOW_H_
#define _CHILD_WINDOW_H_

#include "Types.h"

class cChildWindow
{
public:
	HWND childhWnd;
	HINSTANCE hInt;
	//cCreateWnd Wnd;
	GameEngine::viewPos Position;
	cChildWindow();
	cChildWindow(HWND parent, WNDPROC WndChildProc, char* childClassName, GameEngine::viewPos Pos);
	~cChildWindow();

	bool setParent(HWND parent);

};

#endif