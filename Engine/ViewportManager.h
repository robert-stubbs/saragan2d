//#ifndef _VIEWPORT_MANAGER_H_
//#define _VIEWPORT_MANAGER_H_
//
//#include "ChildWnd.h"
//namespace GameEngine
//{
//	class ViewportManager
//	{
//	public:
//		ViewportManager();
//		~ViewportManager();
//		PIXELFORMATDESCRIPTOR pfd;
//		GLuint PixelFormat;
//
//		HDC   hDC;
//		HGLRC hRC;
//		int keyIndexer;
//		std::vector<int> keys;
//		std::map<int, cChildWindow> viewWindows;
//		std::map<int, Viewport> viewPorts;
//
//		float activeClearColor[4];
//		float inActiveClearColor[4];
//
//		void getDefaultLayout();
//
//		bool createChildWindow(HWND parent, WNDPROC childProc, viewPos Position, std::string name);
//		HDC createNewDC(HWND thishWnd);
//		bool createNewContext(HDC thishDC);
//
//		bool changedActiveView(int x, int y);
//		std::string getActiveViewCamera();
//		cChildWindow* getActiveView();
//
//		bool changeContextPosition(int key, viewPos Position);
//		bool changeContextParent();
//
//		bool updateContext();
//		bool update();
//
//		bool renderContext(Viewport* view);
//		bool render();
//
//		void check_gl_error();
//		glm::vec3 ContextsPosition(int x, int y);
//		glm::vec3 GetCurrentContextPos(int x, int y, Viewport* viewport, cChildWindow* wnd);
//
//		glm::vec3 GetOGLPos(int x, int y, glm::mat4 projection, glm::mat4 view, viewPos pos);
//		glm::vec3 GetOGLPos2D(int x, int y, glm::mat4 projection);
//
//	};
//}
//#endif