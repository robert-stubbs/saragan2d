#ifndef _RENDERER_H_
#define _RENDERER_H_

class StateMachine;
class SystemManager;
class Shader;

#include "Object.h"

class Renderer
{
public:
	PIXELFORMATDESCRIPTOR pfd;
	HGLRC hRC;
	HDC   hDC;
	bool  fullscreen;

	Shader* shader; // Our GLSL shader 
	Shader* animShader; // Our GLSL shader 
	Shader* CurrentShader; // Our GLSL shader 

	Renderer();
	virtual ~Renderer();

	virtual bool CreateDC(HWND thisHwnd, PIXELFORMATDESCRIPTOR& pfd, HDC& hDC) = 0;
	virtual bool SetUpContext(HWND hWnd, PIXELFORMATDESCRIPTOR& pfd, HGLRC& hRC, HDC& hDC) = 0;
	virtual bool SetUpShaders() = 0;

	virtual bool init(HWND hWnd) = 0;
	virtual bool PostInit() = 0;
	virtual bool load() = 0;
	virtual bool Update(float DeltaTime) = 0;
	virtual bool UpdateOrtho(float DeltaTime) = 0;
	virtual void render(StateMachine* GameFSM, SystemManager* System, glm::mat4 projection, glm::mat4 view) = 0;
	virtual void renderOrtho(StateMachine* GameFSM, SystemManager* System, glm::mat4 projection, glm::mat4 view) = 0;
	virtual bool cleanup() = 0;

	virtual glm::vec3 GetWorldPos(int x, int y, glm::mat4 projection, glm::mat4 view) = 0;
	virtual glm::vec3 GetWorldPos2D(int x, int y, glm::mat4 projection, glm::mat4 view) = 0;

	virtual bool ResizeWindow(int Width, int Height) = 0;

	virtual void GenerateBuffer(unsigned int& VAIO, unsigned int& VBO, std::vector<vert>& verts) = 0;
	virtual void ReGenerateBuffer(unsigned int& VAIO, unsigned int& VBO, std::vector<vert>& verts) = 0;
	virtual bool UpdateBuffer(unsigned int& VBO, std::vector<vert>& verts) = 0;
	virtual void GenerateIndexBuffer(GLuint& VAIO, GLuint& IBO, GLuint& VBO, std::vector<vert>& verts, std::vector<int>& VertIndex) = 0;
};

#endif // !_RENDERER_H_
