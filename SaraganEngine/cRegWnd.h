#ifndef _REG_WND_H_
#define _REG_WND_H_

class cRegWnd
{
public:
	bool screen_fullscreen;
	int screen_width;
	int screen_height;
	HINSTANCE hInst;

	cRegWnd(HINSTANCE hInstance, WNDPROC WndProc, bool fullscreen = false, int width = 800, int height = 600);
	void Register();

protected:
	WNDCLASSEX wc;

};


#endif