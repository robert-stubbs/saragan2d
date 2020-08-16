#ifndef _OPENGL_RENDERER_H_
#define _OPENGL_RENDERER_H_

#include "Renderer.h"

class Renderer;

class OpenGLRenderer : public Renderer
{
public:
	GLuint PixelFormat = 0;

	OpenGLRenderer();
	virtual ~OpenGLRenderer() override;

	virtual bool CreateDC(HWND thisHwnd, PIXELFORMATDESCRIPTOR& pfd, HDC& hDC) override;
	virtual bool SetUpContext(HWND hWnd, PIXELFORMATDESCRIPTOR& pfd, HGLRC& hRC, HDC& hDC) override;
	virtual bool SetUpShaders() override;

	virtual bool init(HWND hWnd) override;
	virtual bool PostInit() override;
	virtual bool load() override;
	virtual bool Update(float DeltaTime) override;
	virtual bool UpdateOrtho(float DeltaTime) override;
	virtual void render() override;
	virtual void renderOrtho() override;
	virtual bool cleanup() override;

	void check_gl_error();
	static void check_error();

	virtual bool ResizeWindow(int Width, int Height);
};

#endif