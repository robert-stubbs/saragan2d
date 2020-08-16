#include "EnginePCH.h"
#include "OpenGLRenderer.h"
#include "Renderer.h"

#include "cErrorLogger.h"

OpenGLRenderer::OpenGLRenderer()
{

}

OpenGLRenderer::~OpenGLRenderer()
{

}

 bool OpenGLRenderer::CreateDC(HWND thisHwnd, PIXELFORMATDESCRIPTOR& pfd, HDC& hDC)
 {	
	 // generate new context, sore in map
	 if (!(hDC = GetDC(thishWnd)))                         // Did We Get A Device Context?
	 {								// Reset The Display
		 cErrorLogger::Log().WriteToConsole("#### Can't Create A GL Device Context ####\n");

		 OpenGLRenderer::check_error();
		 return false;								 // Return FALSE
	 }

	 if (!pfd.dwFlags || PixelFormat == 0)
	 {
		 if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
		 {
			 cErrorLogger::Log().WriteToConsole("#### Can't Find A Suitable PixelFormat ####\n");
			 OpenGLRenderer::check_error();
			 return false;
		 }
	 }


	 if (SetPixelFormat(hDC, PixelFormat, &pfd) == FALSE)
	 {
		 cErrorLogger::Log().WriteToConsole("#### SetPixelFormat failed ####\n");
		 OpenGLRenderer::check_error();
		 return false;
	 }

	 return true;

 }

 bool OpenGLRenderer::SetUpContext(HWND hWnd, PIXELFORMATDESCRIPTOR& pfd, HGLRC& hRC, HDC& hDC)
 {
	 pfd =												// pfd Tells Windows How We Want Things To Be
	 {
		 sizeof(PIXELFORMATDESCRIPTOR),                  // Size Of This Pixel Format Descriptor
		 1,												// Version Number
		 PFD_DRAW_TO_WINDOW |							// Format Must Support Window
		 PFD_SUPPORT_OPENGL |							// Format Must Support OpenGL
		 PFD_DOUBLEBUFFER,								// Must Support Double Buffering
		 PFD_TYPE_RGBA,									// Request An RGBA Format
		 24,												// Select Our Color Depth
		 0, 0, 0, 0, 0, 0,								// Color Bits Ignored
		 0,												// No Alpha Buffer
		 0,												// Shift Bit Ignored
		 0,												// No Accumulation Buffer
		 0, 0, 0, 0,										// Accumulation Bits Ignored
		 32,												// 16Bit Z-Buffer (Depth Buffer)
		 0,												// No Stencil Buffer
		 0,												// No Auxiliary Buffer
		 PFD_MAIN_PLANE,									// Main Drawing Layer
		 0,												// Reserved
		 0, 0, 0											// Layer Masks Ignored
	 };
	 PixelFormat = 0;

	 createDC(hWnd, pfd, hDC);

	 HGLRC tempOpenGLContext;

	 if (!(tempOpenGLContext = wglCreateContext(hDC)))
	 {
		 cErrorLogger::Log().WriteToConsole("#### Can't Create A GL Rendering Context ####\n");
		 OpenGLRenderer::check_error();
		 return false;
	 }


	 if (!wglMakeCurrent(hDC, tempOpenGLContext))
	 {
		 cErrorLogger::Log().WriteToConsole("#### Can't Activate The GL Rendering Context ####\n");
		 cEngine::check_error();
		 return false;
	 }

	 glewExperimental = TRUE;
	 GLenum err = glewInit();
	 if (err != GLEW_OK)
	 {
		 cErrorLogger::Log().WriteToConsole("####glewInit failed, aborting ####\n");
		 OpenGLRenderer::check_error();
	 }

	 int attributes[] = {
		 WGL_CONTEXT_MAJOR_VERSION_ARB, 3, // Set the MAJOR version of OpenGL to 3
		 WGL_CONTEXT_MINOR_VERSION_ARB, 3, // Set the MINOR version of OpenGL to 2
		 WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, // Set our OpenGL context to be forward compatible
		 0
	 };

	 if (wglewIsSupported("WGL_ARB_create_context") == 1) { // If the OpenGL 3.x context creation extension is available

		 hRC = wglCreateContextAttribsARB(hDC, NULL, attributes); // Create and OpenGL 3.x context based on the given attributes
		 wglMakeCurrent(NULL, NULL); // Remove the temporary context from being active
		 wglDeleteContext(tempOpenGLContext); // Delete the temporary OpenGL 2.1 context
		 // Make our OpenGL 3.0 context current
		 if (!wglMakeCurrent(hDC, hRC))
		 {
			 cErrorLogger::Log().WriteToConsole("#### Can't Activate The GL Rendering Context ####\n");
			 OpenGLRenderer::check_error();
			 return false;
		 }
	 }
	 else {
		 hRC = tempOpenGLContext; // If we didn't have support for OpenGL 3.x and up, use the OpenGL 2.1 context

	 }

	 int Major = 0;
	 int Minor = 0;

	 glGetIntegerv(GL_MAJOR_VERSION, &Major); // major = 3
	 glGetIntegerv(GL_MINOR_VERSION, &Minor); // minor = 2

	 cErrorLogger::Log().WriteToConsole("> OpenGL version: ");
	 cErrorLogger::Log().WriteToConsole(Major);
	 cErrorLogger::Log().WriteToConsole(Minor);
	 cErrorLogger::Log().WriteToConsole("\n");

	 return true;
 }

 bool OpenGLRenderer::SetUpShaders()
 {

 }

 bool OpenGLRenderer::init(HWND hWnd)
 {

 }

 bool OpenGLRenderer::PostInit()
 {

 }

 bool OpenGLRenderer::load()
 {

 }

 bool OpenGLRenderer::Update(float DeltaTime)
 {

 }

 bool OpenGLRenderer::UpdateOrtho(float DeltaTime)
 {

 }

 void OpenGLRenderer::render()
 {

 }

 void OpenGLRenderer::renderOrtho()
 {

 }

 bool OpenGLRenderer::cleanup()
 {

 }

 bool OpenGLRenderer::ResizeWindow(int Width, int Height)
 {

 }

 void OpenGLRenderer::check_gl_error()
 {

 }

 void OpenGLRenderer::check_error()
 {

 }