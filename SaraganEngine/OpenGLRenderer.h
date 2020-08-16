#ifndef _OPENGL_RENDERER_H_
#define _OPENGL_RENDERER_H_

#include "Renderer.h"

class Renderer;

class OpenGLRenderer : public Renderer
{
	GLuint& PixelFormat;

	OpenGLRenderer();
	virtual ~OpenGLRenderer();

	virtual bool CreateDC(HWND thisHwnd, PIXELFORMATDESCRIPTOR& pfd, HDC& hDC);
	virtual bool SetUpContext(HWND hWnd, PIXELFORMATDESCRIPTOR& pfd, HGLRC& hRC, HDC& hDC);
	virtual bool SetUpShaders();

	virtual bool init(HWND hWnd);
	virtual bool PostInit();
	virtual bool load();
	virtual bool Update(float DeltaTime);
	virtual bool UpdateOrtho(float DeltaTime);
	virtual void render();
	virtual void renderOrtho();
	virtual bool cleanup();

	void check_gl_error();
	static void check_error();

	virtual bool ResizeWindow(int Width, int Height);
};

#endif