#ifndef _ENGINE_H_	
#define _ENGINE_H_

class Engine
{
	Engine();
	~Engine();


	bool init(HWND hWnd);
	bool PostInit();
	bool load();
	bool Update(float DeltaTime);
	bool UpdateOrth(float DeltaTime);
	void render();
	void renderOrth();
	bool cleanup();

	bool ResizeWindow(int Width, int Height);

	void KeyDown(UINT Msg, WPARAM wParam, LPARAM lParam);
	void KeyUp(UINT Msg, WPARAM wParam, LPARAM lParam);

	void MouseDown(UINT Msg, WPARAM wParam, LPARAM lParam);
	void MouseUp(UINT Msg, WPARAM wParam, LPARAM lParam);
	void MouseMove(UINT Msg, WPARAM wParam, LPARAM lParam);

};

#endif // !_ENGINE_H_
