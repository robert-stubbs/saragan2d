#ifndef _CHILD_WINDOW_H_
#define _CHILD_WINDOW_H_

#include "Viewport.h"
//#include "cCreateWnd.h"

class cChildWindow
{
public:
	HWND childhWnd;
	HINSTANCE hInt;
	//cCreateWnd Wnd;
	viewPos Position;
	cChildWindow();
	cChildWindow(HWND parent, WNDPROC WndChildProc, char* childClassName, viewPos Pos);
	~cChildWindow();

	bool setParent(HWND parent);

};

#endif