#include "EnginePCH.h"
//#include "ViewportManager.h"
//#include "Viewport.h"
//#include "Types.h"
//
//namespace GameEngine
//{
//	ViewportManager::ViewportManager()
//	{
//		pfd =												// pfd Tells Windows How We Want Things To Be
//		{
//			sizeof(PIXELFORMATDESCRIPTOR),                  // Size Of This Pixel Format Descriptor
//			1,												// Version Number
//			PFD_DRAW_TO_WINDOW |							// Format Must Support Window
//			PFD_SUPPORT_OPENGL |							// Format Must Support OpenGL
//			PFD_DOUBLEBUFFER,								// Must Support Double Buffering
//			PFD_TYPE_RGBA,									// Request An RGBA Format
//			24,												// Select Our Color Depth
//			0, 0, 0, 0, 0, 0,								// Color Bits Ignored
//			0,												// No Alpha Buffer
//			0,												// Shift Bit Ignored
//			0,												// No Accumulation Buffer
//			0, 0, 0, 0,										// Accumulation Bits Ignored
//			32,												// 16Bit Z-Buffer (Depth Buffer)
//			0,												// No Stencil Buffer
//			0,												// No Auxiliary Buffer
//			PFD_MAIN_PLANE,									// Main Drawing Layer
//			0,												// Reserved
//			0, 0, 0											// Layer Masks Ignored
//		};
//		PixelFormat = 0;
//		keyIndexer = 0;
//		viewWindows.clear();
//		keys.clear();
//		viewPorts.clear();
//
//		activeClearColor[0] = 0.3f;
//		activeClearColor[1] = 0.3f;
//		activeClearColor[2] = 0.3f;
//		activeClearColor[3] = 0.0f;
//
//		inActiveClearColor[0] = 0.1f;
//		inActiveClearColor[1] = 0.1f;
//		inActiveClearColor[2] = 0.1f;
//		inActiveClearColor[3] = 0.0f;
//
//	}
//
//	ViewportManager::~ViewportManager()
//	{
//		for (size_t i = 0; i < keys.size(); i++)
//		{
//			viewPorts[keys.at(i)].CleanUp();
//		}
//		viewPorts.clear();
//		keys.clear();
//
//		if (hRC)
//		{
//			if (!wglMakeCurrent(NULL, NULL))                 // Are We Able To Release The DC And RC Contexts?
//			{
//				//MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
//			}
//		}
//
//		if (!wglDeleteContext(hRC))
//		{
//			//MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
//		}
//		hRC = NULL;
//	}
//
//	void ViewportManager::getDefaultLayout()
//	{
//		// get default layout stored in the ini file
//		// default is 1 Full screen (can be changed)
//
//
//	}
//
//	bool ViewportManager::createChildWindow(HWND parent, WNDPROC childProc, viewPos Position, std::string name)
//	{
//		int current = keyIndexer;
//
//		//cChildWindow* newChild = new cChildWindow(clientArea->childhWnd, childProc, "FOO", Position);
//
//		viewPos contextPos = { 0, 0, Position.width, Position.height };
//
//		Viewport* viewPort;
//
//		if ((int)viewPorts.size() <= 0)
//		{
//			//hDC = createNewDC(newChild->childhWnd);
//			createNewContext(hDC);
//			viewPort = new Viewport(hDC, contextPos);
//		}
//		else {
//
//			//hDC = createNewDC(newChild->childhWnd);
//			viewPort = new Viewport(hDC, contextPos);
//		}
//
//
//		//cCameraBase* def = new cCameraBase(Perspective, Position.width, Position.height);
//		//camNames.push_back(name);
//		//Cameras[name] = *def;
//		viewPort->CameraName = name;
//		viewPort->isLoaded = true;
//		//viewWindows[current] = *newChild;
//		viewPorts[current] = *viewPort;
//		keys.push_back(current);
//
//		viewPorts[current].ResizeWindow(contextPos);
//
//		keyIndexer++;
//		return true;
//	}
//
//	HDC ViewportManager::createNewDC(HWND thishWnd)
//	{
//		// generate new context, sore in map
//		if (!(hDC = GetDC(thishWnd)))                         // Did We Get A Device Context?
//		{								// Reset The Display
//			//Er->WriteToConsole("#### Can't Create A GL Device Context ####\n");
//			check_gl_error();
//			return false;								 // Return FALSE
//		}
//
//		if (!pfd.dwFlags || PixelFormat == 0)
//		{
//			if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
//			{
//				//Er->WriteToConsole("#### Can't Find A Suitable PixelFormat ####\n");
//				check_gl_error();
//				return false;
//			}
//		}
//
//
//		if (SetPixelFormat(hDC, PixelFormat, &pfd) == FALSE)
//		{
//			//Er->WriteToConsole("#### SetPixelFormat failed ####\n");
//			check_gl_error();
//			return false;
//		}
//		return hDC;
//	}
//
//	bool ViewportManager::createNewContext(HDC thishDC)
//	{
//		HGLRC tempOpenGLContext;
//
//		if (!(tempOpenGLContext = wglCreateContext(thishDC)))
//		{
//			//Er->WriteToConsole("#### Can't Create A GL Rendering Context ####\n");
//			check_gl_error();
//			return false;
//		}
//
//
//		if (!wglMakeCurrent(thishDC, tempOpenGLContext))
//		{
//			//Er->WriteToConsole("#### Can't Activate The GL Rendering Context ####\n");
//			check_gl_error();
//			return false;
//		}
//
//		glewExperimental = TRUE;
//		GLenum err = glewInit();
//		if (err != GLEW_OK)
//		{
//			//Er->WriteToConsole("####glewInit failed, aborting ####\n");
//			check_gl_error();
//		}
//
//		int attributes[] = {
//			WGL_CONTEXT_MAJOR_VERSION_ARB, 3, // Set the MAJOR version of OpenGL to 3
//			WGL_CONTEXT_MINOR_VERSION_ARB, 3, // Set the MINOR version of OpenGL to 2
//			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, // Set our OpenGL context to be forward compatible
//			0
//		};
//
//		if (wglewIsSupported("WGL_ARB_create_context") == 1) { // If the OpenGL 3.x context creation extension is available
//
//			hRC = wglCreateContextAttribsARB(thishDC, NULL, attributes); // Create and OpenGL 3.x context based on the given attributes
//			wglMakeCurrent(NULL, NULL); // Remove the temporary context from being active
//			wglDeleteContext(tempOpenGLContext); // Delete the temporary OpenGL 2.1 context
//			// Make our OpenGL 3.0 context current
//			if (!wglMakeCurrent(thishDC, hRC))
//			{
//				//Er->WriteToConsole("#### Can't Activate The GL Rendering Context ####\n");
//				check_gl_error();
//				return false;
//			}
//		}
//		else {
//			hRC = tempOpenGLContext; // If we didn't have support for OpenGL 3.x and up, use the OpenGL 2.1 context
//
//		}
//
//		int Major = 0;
//		int Minor = 0;
//
//		glGetIntegerv(GL_MAJOR_VERSION, &Major); // major = 3
//		glGetIntegerv(GL_MINOR_VERSION, &Minor); // minor = 2
//
//		//Er->WriteToConsole("> OpenGL version: ");
//		//Er->WriteToConsole(Major);
//		//Er->WriteToConsole(Minor);
//		//Er->WriteToConsole("\n");
//
//		return true;
//	}
//
//	bool ViewportManager::changeContextPosition(int key, viewPos Position)
//	{
//		MoveWindow(viewWindows[key].childhWnd, (int)Position.x, (int)Position.y, (int)Position.width, (int)Position.height, true);
//		viewWindows[key].Position = Position;
//		if (viewPorts[key].isLoaded)
//		{
//			viewPos contextPos = { 0, 0, Position.width, Position.height };
//			viewPorts[key].ResizeWindow(contextPos);
//		}
//
//		return true;
//	}
//
//	bool changeContextParent()
//	{
//
//		return true;
//	}
//
//	bool ViewportManager::updateContext()
//	{
//		// if view isActive;
//
//		return true;
//	}
//
//	bool ViewportManager::update()
//	{
//
//
//
//		return true;
//	}
//
//	bool ViewportManager::renderContext(Viewport* view)
//	{
//
//		//if view isActive;
//		if (view->isCurrent)
//		{
//			glClearColor(activeClearColor[0], activeClearColor[1], activeClearColor[2], activeClearColor[3]);
//		}
//		else {
//			glClearColor(inActiveClearColor[0], inActiveClearColor[1], inActiveClearColor[2], inActiveClearColor[3]);
//		}
//		view->Render();
//		return true;
//	}
//
//	bool ViewportManager::render()
//	{
//		for (size_t i = 0; i < keys.size(); i++)
//		{
//			renderContext(&viewPorts[keys.at(i)]);
//		}
//		return true;
//	}
//
//	void ViewportManager::check_gl_error() {
//		GLenum err(glGetError());
//
//		//if (!err)
//		//{
//		//	Er->WriteToConsole("> No Errors safe\n");
//		//	return;
//		//}
//		//else if (err != GL_NO_ERROR) {
//		//	string error;
//
//		//	switch (err) {
//		//	case GL_INVALID_OPERATION:      error = "INVALID_OPERATION";      break;
//		//	case GL_INVALID_ENUM:           error = "INVALID_ENUM";           break;
//		//	case GL_INVALID_VALUE:          error = "INVALID_VALUE";          break;
//		//	case GL_OUT_OF_MEMORY:          error = "OUT_OF_MEMORY";          break;
//		//	case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
//		//	}
//
//		//	Er->WriteToConsole("######################### GL_");
//		//	Er->WriteToConsole(error.c_str());
//		//	Er->WriteToConsole(" #########################\n");
//		//	err = glGetError();
//		//}
//	}
//
//
//	bool ViewportManager::changedActiveView(int x, int y)
//	{
//		//float xPosition = (float)clientDef.left + (x - clientDef.left);
//		//float yPosition = (float)clientDef.top + (y - clientDef.top);
//
//		bool hasChanged = false;
//
//		//for (size_t i = 0; i < keys.size(); i++)
//		//{
//		//	cChildWindow* wnd = &viewWindows[keys.at(i)];
//		//	Viewport* view = &viewPorts[keys.at(i)];
//		//	viewPos position = wnd->Position;
//		//	if ((position.x <= xPosition && (position.x + position.width) >= xPosition)
//		//		&& (position.y <= yPosition && (position.y + position.height) >= yPosition))
//		//	{
//		//		if (view->isCurrent)
//		//		{
//		//			hasChanged = false;
//		//		}
//
//		//		view->isCurrent = true;
//		//	}
//		//	else {
//		//		if (view->isCurrent)
//		//		{
//		//			hasChanged = true;
//		//		}
//		//		view->isCurrent = false;
//		//	}
//		//}
//		return hasChanged;
//	}
//
//	std::string ViewportManager::getActiveViewCamera()
//	{
//		for (size_t i = 0; i < keys.size(); i++)
//		{
//			Viewport* view = &viewPorts[keys.at(i)];
//			if (view->isCurrent)
//			{
//				return view->CameraName;
//			}
//		}
//		return "";
//	}
//
//	cChildWindow* ViewportManager::getActiveView()
//	{
//		for (size_t i = 0; i < keys.size(); i++)
//		{
//			Viewport* view = &viewPorts[keys.at(i)];
//			if (view->isCurrent)
//			{
//				return &viewWindows[keys.at(i)];
//			}
//		}
//		return nullptr;
//	}
//
//	glm::vec3 ViewportManager::ContextsPosition(int x, int y)
//	{
//		//float xPosition = (float)clientDef.left + (x - clientDef.left);
//		//float yPosition = (float)clientDef.top + (y - clientDef.top);
//
//		//for (size_t i = 0; i < keys.size(); i++)
//		//{
//		//	cChildWindow* wnd = &viewWindows[keys.at(i)];
//		//	viewPos position = wnd->Position;
//		//	if ((position.x <= xPosition && (position.x + position.width) >= xPosition)
//		//		&& (position.y <= yPosition && (position.y + position.height) >= yPosition))
//		//	{
//		//		Viewport* view = &viewPorts[keys.at(i)];
//		//		return GetCurrentContextPos((int)xPosition, (int)yPosition, view, wnd);
//		//		break;
//		//	}
//		//}
//		return glm::vec3();
//	}
//
//	glm::vec3 ViewportManager::GetCurrentContextPos(int x, int y, Viewport* viewport, cChildWindow* wnd)
//	{
//
//		/*cCameraBase* current = &Cameras[viewport->CameraName];
//
//		if (current->type == Perspective)
//		{
//			POINT mouse;
//			GetCursorPos(&mouse);
//			ScreenToClient(wnd->childhWnd, &mouse);
//			return GetOGLPos(mouse.x, mouse.y, Cameras[viewport->CameraName].Projection, Cameras[viewport->CameraName].View, current->pos);
//		}*/
//
//		return glm::vec3();// GetOGLPos2D(x, y, Cameras[viewport->CameraName].Projection);
//	}
//
//	glm::vec3 ViewportManager::GetOGLPos(int x, int y, glm::mat4 projection, glm::mat4 view, viewPos pos)
//	{
//
//		GLint ViewSize[4] = { (GLint)pos.x, (GLint)pos.y, (GLint)pos.width, (GLint)pos.height };
//		GLfloat winY, z;
//		winY = (GLfloat)(ViewSize[1] + ViewSize[3]) - y;
//
//		glReadPixels((GLint)x, (GLint)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
//
//		glm::vec3 nearPos = glm::unProject(glm::vec3((double)x, (double)winY, (double)z), view, projection, glm::vec4(ViewSize[0], ViewSize[1], ViewSize[2], ViewSize[3]));
//
//		return nearPos;
//	}
//
//	glm::vec3 ViewportManager::GetOGLPos2D(int x, int y, glm::mat4 projection)
//	{
//		GLint viewport[4];
//		GLfloat winY;
//		GLfloat z = -1;
//		glGetIntegerv(GL_VIEWPORT, viewport);
//
//		glm::vec4 viewPort = glm::vec4(viewport[0], viewport[1], viewport[2], viewport[3]);
//
//		winY = (GLfloat)(viewport[1] + viewport[3]) - y;
//
//
//		glm::mat4 view = glm::mat4();
//		//float aspect = (float)WIDTH / (float)HEIGHT;
//		float aspect = (float)800 / (float)600;
//
//		glm::vec3 nearPos = glm::unProject(glm::vec3((double)x, (double)winY, (double)z), view, projection, viewPort);
//
//		return nearPos;
//	}
//}