#ifndef _OPENGL_RENDERER_H_
#define _OPENGL_RENDERER_H_

#include "Renderer.h"


class OpenGLShader;
class StateMachine;
class SystemManager;

class OpenGLRenderer : public Renderer
{
public:
	GLuint PixelFormat = 0;
	OpenGLShader* shader; // Our GLSL shader 
	OpenGLShader* animShader; // Our GLSL shader 
	OpenGLShader* CurrentShader; // Our GLSL shader 

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

	virtual void render(StateMachine* GameFSM, SystemManager* System, glm::mat4 projection, glm::mat4 view) override;
	virtual void renderOrtho(StateMachine* GameFSM, SystemManager* System, glm::mat4 projection, glm::mat4 view) override;
	
	virtual bool cleanup() override;

	void check_gl_error();
	static void check_error();


	virtual glm::vec3 GetWorldPos(int x, int y, glm::mat4 projection, glm::mat4 view);
	virtual glm::vec3 GetWorldPos2D(int x, int y, glm::mat4 projection, glm::mat4 view);

	virtual bool ResizeWindow(int Width, int Height);
};

#endif