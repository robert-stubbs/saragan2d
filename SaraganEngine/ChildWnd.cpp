#include "EnginePCH.h"
#include "ChildWnd.h"
#include "Viewport.h"
#include "cRegWnd.h"

cChildWindow::cChildWindow()
{

}

cChildWindow::cChildWindow(HWND parent, WNDPROC WndChildProc, char* childClassName, viewPos Pos)
{

	cRegWnd WinApp(hInt, WndChildProc, childClassName);
	WinApp.Register();

	//childhWnd = Wnd.Create(hInt, (int)Pos.width, (int)Pos.height, CLIENTCREATESTRUCT(), parent, WS_CHILD | WS_CLIPCHILDREN | WS_BORDER, 0, (int)Pos.x, (int)Pos.y, childClassName);
	Position = Pos;

	//Wnd.show();

}

cChildWindow::~cChildWindow()
{



}

bool cChildWindow::setParent(HWND parent)
{
	if (parent == NULL)
	{
		SetParent(childhWnd, NULL);

		SetWindowLong(childhWnd, GWL_EXSTYLE, 0);
		SetWindowLong(childhWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
		SetWindowPos(childhWnd, HWND_TOP, (int)Position.x, (int)Position.y, (int)Position.width, (int)Position.height, SWP_SHOWWINDOW | SWP_FRAMECHANGED);
	}
	else {
		SetParent(childhWnd, parent);
		SetWindowLong(childhWnd, GWL_EXSTYLE, WS_EX_CLIENTEDGE);
		SetWindowLong(childhWnd, GWL_STYLE, NULL);
		SetWindowPos(childhWnd, HWND_TOP, (int)Position.x, (int)Position.y, (int)Position.width, (int)Position.height, SWP_SHOWWINDOW | SWP_FRAMECHANGED);
	}

	return true;
}