#ifndef _CREATE_WND_H_
#define _CREATE_WND_H_

class cRegWnd;

class cCreateWnd
{
public:

	cRegWnd* reg;

	bool fullscreen;

	HWND hWnd;
	cCreateWnd(cRegWnd* regwnd);
	~cCreateWnd();

	HWND Create(
		HWND parent = NULL,
		DWORD dStyle = WS_OVERLAPPEDWINDOW,
		DWORD dXStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		int xPos = 0,
		int yPos = 0);

	BOOL show(int dCmdShow = SW_SHOWNORMAL);


	operator HWND();

};

#endif