#include "EnginePCH.h"


#include "cCreateWnd.h"
#include "cRegWnd.h"

cCreateWnd::cCreateWnd(cRegWnd* regwnd)
{
	fullscreen = false;
	hWnd = NULL;

	reg = regwnd;
}


cCreateWnd::~cCreateWnd()
{
}


HWND cCreateWnd::Create(HWND parent, DWORD dStyle, DWORD dXStyle, int xPos, int yPos)
{
	if (reg->screen_fullscreen)
	{
		dXStyle = WS_EX_APPWINDOW;
		dStyle = WS_POPUP;
		ShowCursor(FALSE);
	}

	hWnd = CreateWindowEx(dXStyle, CLASSNAME, WNDNAME, dStyle, xPos, yPos, reg->screen_width, reg->screen_height, parent, NULL, reg->hInst, this);

	if (hWnd == NULL)
	{
		MessageBox(NULL, TEXT("Create Window Failed!"), TEXT("Error"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	return hWnd;
}

BOOL cCreateWnd::show(int dCmdShow)
{
	if (ShowWindow(hWnd, dCmdShow) && UpdateWindow(hWnd))
	{
		return TRUE;
	}
	return FALSE;
}

cCreateWnd::operator HWND()
{
	return hWnd;
}
