#include "EnginePCH.h"
#include "OpenGLRenderer.h"
#include "Renderer.h"

#include "cErrorLogger.h"
#include "OpenGLShader.h"
#include "StateMachine.h"
#include "SystemManager.h"

OpenGLRenderer::OpenGLRenderer() : Renderer()
{
}

OpenGLRenderer::~OpenGLRenderer()
{

}

 bool OpenGLRenderer::CreateDC(HWND thisHwnd, PIXELFORMATDESCRIPTOR& pfd, HDC& hDC)
 {	
	 // generate new context, sore in map
	 if (!(hDC = GetDC(thisHwnd)))                         // Did We Get A Device Context?
	 {								// Reset The Display
		 cErrorLogger::Log().WriteToConsole("#### Can't Create A GL Device Context ####");

		 OpenGLRenderer::check_error();
		 return false;								 // Return FALSE
	 }

	 if (!pfd.dwFlags || PixelFormat == 0)
	 {
		 if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
		 {
			 cErrorLogger::Log().WriteToConsole("#### Can't Find A Suitable PixelFormat ####");
			 OpenGLRenderer::check_error();
			 return false;
		 }
	 }


	 if (SetPixelFormat(hDC, PixelFormat, &pfd) == FALSE)
	 {
		 cErrorLogger::Log().WriteToConsole("#### SetPixelFormat failed ####");
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

	 CreateDC(hWnd, pfd, hDC);

	 HGLRC tempOpenGLContext;

	 if (!(tempOpenGLContext = wglCreateContext(hDC)))
	 {
		 cErrorLogger::Log().WriteToConsole("#### Can't Create A GL Rendering Context ####");
		 OpenGLRenderer::check_error();
		 return false;
	 }


	 if (!wglMakeCurrent(hDC, tempOpenGLContext))
	 {
		 cErrorLogger::Log().WriteToConsole("#### Can't Activate The GL Rendering Context ####");
		 OpenGLRenderer::check_error();
		 return false;
	 }

	 glewExperimental = TRUE;
	 GLenum err = glewInit();
	 if (err != GLEW_OK)
	 {
		 cErrorLogger::Log().WriteToConsole("####glewInit failed, aborting ####");
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
			 cErrorLogger::Log().WriteToConsole("#### Can't Activate The GL Rendering Context ####");
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
	 cErrorLogger::Log().WriteToConsole("");

	 return true;
 }

bool OpenGLRenderer::SetUpShaders()
{
	std::string asset_dir = "C:/Assets/";

	shader = new OpenGLShader();
	shader->init(asset_dir + "Shaders/VertexShader.glsl", asset_dir + "Shaders/FragmentShader.glsl");

	animShader = new OpenGLShader();
	animShader->isAnimShader = true;
	animShader->init(asset_dir + "Shaders/VertexShaderAnim.glsl", asset_dir + "Shaders/FragmentShaderAnim.glsl");

	CurrentShader = shader;
	CurrentShader->bind();

	return false;
}

 bool OpenGLRenderer::init(HWND hWnd)
 {
	 if (!SetUpContext(hWnd, pfd, hRC, hDC))
	 {
		 cErrorLogger::Log().WriteToConsole("Failed to setup Context");
		 return false;
	 }

	 if (!SetUpShaders())
	 {
		 cErrorLogger::Log().WriteToConsole("Failed to setup Shaders\n");
		 return false;
	 }

	 return true;
 }

 bool OpenGLRenderer::PostInit()
 {
	 check_gl_error();

	 glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	 glClearDepth(1.0f);

	 // Enable depth test
	 glEnable(GL_DEPTH_TEST);
	 // Accept fragment if it closer to the camera than the former one
	 glDepthFunc(GL_LESS);

	 glShadeModel(GL_SMOOTH);

	 return true;
 }

 bool OpenGLRenderer::load()
 {
	 return false;
 }

 bool OpenGLRenderer::Update(float DeltaTime)
 {

	 return true;
 }

 bool OpenGLRenderer::UpdateOrtho(float DeltaTime)
 {

	 return true;
 }

 void OpenGLRenderer::render(StateMachine* GameFSM, SystemManager* System, glm::mat4 projection, glm::mat4 view)
 {
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	 if (CurrentShader != shader)
	 {
		 CurrentShader->unbind();
		 CurrentShader = shader;
		 CurrentShader->bind();
	 }

	 glUniform1i(CurrentShader->isText, 0);
	 glUniformMatrix4fv(CurrentShader->projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projection)); // Send our view matrix to the shader 
	 glUniformMatrix4fv(CurrentShader->viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(view)); // Send our view matrix to the shader  
	 glUniformMatrix4fv(CurrentShader->modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

	 GameFSM->Render();
	 System->Render();

	 if (CurrentShader != animShader)
	 {
		 CurrentShader->unbind();
		 CurrentShader = animShader;
		 CurrentShader->bind();
	 }

	 glUniformMatrix4fv(CurrentShader->projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projection)); // Send our view matrix to the shader 
	 glUniformMatrix4fv(CurrentShader->viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(view)); // Send our view matrix to the shader  

	 System->RenderAnim();
	 GameFSM->RenderAnim();

 }

 void OpenGLRenderer::renderOrtho(StateMachine* GameFSM, SystemManager* System, glm::mat4 projection, glm::mat4 view)
 {
	 if (CurrentShader != shader)
	 {
		 CurrentShader->unbind();
		 CurrentShader = shader;
		 CurrentShader->bind();
	 }

	 glUniformMatrix4fv(CurrentShader->projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projection)); // Send our view matrix to the shader 
	 glUniformMatrix4fv(CurrentShader->viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(view)); // Send our view matrix to the shader  
	 glUniformMatrix4fv(CurrentShader->modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

	 GameFSM->RenderOrth();
	 System->RenderUI();

	 SwapBuffers(hDC);
 }

 bool OpenGLRenderer::cleanup()
 {
	 if (fullscreen)
	 {
		 ChangeDisplaySettings(NULL, 0);
		 ShowCursor(true);
	 }

	 if (hRC)
	 {
		 if (!wglMakeCurrent(NULL, NULL))                 // Are We Able To Release The DC And RC Contexts?
		 {
			 MessageBox(NULL, L"Release Of DC And RC Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		 }
	 }

	 if (!wglDeleteContext(hRC))
	 {
		 MessageBox(NULL, L"Release Rendering Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
	 }
	 hRC = NULL;

	 return true;
 }

 bool OpenGLRenderer::ResizeWindow(int Width, int Height)
 {
	 if (Height == 0)
	 {
		 Height = 1;
	 }

	 glViewport(0, 0, Width, Height);
	 //ProjectionMatrix = glm::perspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 400.0f);

	 return true;
 }

 void OpenGLRenderer::check_gl_error()
 {
	 OpenGLRenderer::check_error();
 }

 void OpenGLRenderer::check_error()
 {
	 GLenum err(glGetError());
	 std::string error;

	 if (!err)
	 {
		 return;
	 }
	 else if (err != GL_NO_ERROR) {

		 switch (err) {
		 case GL_INVALID_OPERATION:      error = "INVALID_OPERATION";      break;
		 case GL_INVALID_ENUM:           error = "INVALID_ENUM";           break;
		 case GL_INVALID_VALUE:          error = "INVALID_VALUE";          break;
		 case GL_OUT_OF_MEMORY:          error = "OUT_OF_MEMORY";          break;
		 case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
		 }

		 err = glGetError();
		 //cout << "Error: " << error << endl;
		 cErrorLogger::Log().WriteToConsole(error);
	 }
 }


 glm::vec3 OpenGLRenderer::GetWorldPos(int x, int y, glm::mat4 projection, glm::mat4 view)
 {
	 GLint viewport[4];
	 GLfloat winY, z;
	 glGetIntegerv(GL_VIEWPORT, viewport);

	 winY = (GLfloat)((viewport[1] + viewport[3]) - y);

	 glReadPixels((GLint)x, (GLint)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);

	 return glm::unProject(glm::vec3((double)x, (double)winY, (double)z), view, projection, glm::vec4(viewport[0], viewport[1], viewport[2], viewport[3]));
	 
 }

 glm::vec3 OpenGLRenderer::GetWorldPos2D(int x, int y, glm::mat4 projection, glm::mat4 view)
 {
	 GLint viewport[4];
	 GLfloat winY;
	 glGetIntegerv(GL_VIEWPORT, viewport);

	 winY = (GLfloat)((viewport[1] + viewport[3]) - y);

	 return glm::unProject(glm::vec3((double)x, (double)winY, 0.0f), view, projection, glm::vec4(viewport[0], viewport[1], viewport[2], viewport[3]));
 }