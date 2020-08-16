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


	virtual glm::vec3 GetWorldPos(int x, int y, glm::mat4 projection, glm::mat4 view) override;
	virtual glm::vec3 GetWorldPos2D(int x, int y, glm::mat4 projection, glm::mat4 view) override;

	virtual bool ResizeWindow(int Width, int Height) override;

	virtual void GenerateBuffer(unsigned int& VAIO, unsigned int& VBO, std::vector<vert>& verts) override;
	virtual void ReGenerateBuffer(unsigned int& VAIO, unsigned int& VBO, std::vector<vert>& verts) override;
	virtual bool UpdateBuffer(unsigned int& VBO, std::vector<vert>& verts) override;
	virtual void GenerateIndexBuffer(GLuint& VAIO, GLuint& IBO, GLuint& VBO, std::vector<vert>& verts, std::vector<int>& VertIndex) override;
};

#endif