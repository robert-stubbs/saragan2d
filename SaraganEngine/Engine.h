#ifndef _ENGINE_H_	
#define _ENGINE_H_

#include "glm/glm.hpp"

class Renderer;
class SystemManager;
class StateMachine;
class EntityManager;

class Engine
{
public:
	Engine();
	~Engine();

	float width;
	float height;

	Renderer* renderer;
	StateMachine* GameFSM;
	SystemManager* System;
	EntityManager* EntityMgr;

	glm::mat4 ProjectionMatrix;
	glm::mat4 viewMatrix; // Store the view matrix  
	glm::mat4 modelMatrix; // Store the model matrix  

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

	static Engine* engine;
	static inline Engine& getEngine() { return *engine; }

};

#endif // !_ENGINE_H_
