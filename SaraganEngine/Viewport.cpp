#include "EnginePCH.h"
#include "EngineLibrary.h"
#include "Viewport.h"


Viewport::Viewport(HDC& DC, viewPos pos)
{
	hDC = DC;
	// reference to attached camera

	isAttached = true;
	layoutPos = fullwindow;
	isLoaded = false;
	isActive = true;
}


Viewport::~Viewport()
{
	CleanUp();
}


bool Viewport::ResizeWindow(viewPos pos)
{

	if (pos.height == 0)
	{
		pos.height = 1;
	}

	//wglMakeCurrent(hDC, VpManager->hRC);
	//glViewport((GLint)pos.x, (GLint)pos.y, (GLsizei)pos.width, (GLsizei)pos.height);

	//if (CameraName.length())
	//{
	//	Cameras[CameraName].updateProjection(pos);
	//}

	return true;
}



void Viewport::ChangeCamera(std::string camName)
{
	//for (size_t i = 0; i < camNames.size(); i++)
	//{
	//	if (camNames.at(i) == camName)
	//	{
	//		CameraName = camName;
	//		break;
	//	}
	//}
	return;
}

bool Viewport::Render()
{
	//wglMakeCurrent(hDC, VpManager->hRC);
	//shader->bind();

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//cCameraBase* current = &Cameras[CameraName];
	//current->Update();
	//glUniformMatrix4fv(shader->projectionMatrixLocation, 1, GL_FALSE, &current->Projection[0][0]); // Send our view matrix to the shader 
	//glUniformMatrix4fv(shader->viewMatrixLocation, 1, GL_FALSE, &current->View[0][0]); // Send our view matrix to the shader  

	//glUniformMatrix4fv(shader->modelMatrixLocation, 1, GL_FALSE, &glm::mat4()[0][0]);

	//if (MapManager->currentMap && MapManager->currentMap->isLoaded)
	//{
	//	MapManager->currentMap->RenderMap(shader);
	//}

	SwapBuffers(hDC);
	return true;
}


void Viewport::CleanUp()
{

}

void Viewport::check_gl_error() {
	GLenum err(glGetError());

	//if (!err)
	//{
	//	Er->WriteToConsole("> No Errors safe\n");
	//	return;
	//}
	//else if (err != GL_NO_ERROR) {
	//	string error;

	//	switch (err) {
	//	case GL_INVALID_OPERATION:      error = "INVALID_OPERATION";      break;
	//	case GL_INVALID_ENUM:           error = "INVALID_ENUM";           break;
	//	case GL_INVALID_VALUE:          error = "INVALID_VALUE";          break;
	//	case GL_OUT_OF_MEMORY:          error = "OUT_OF_MEMORY";          break;
	//	case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
	//	}

	//	Er->WriteToConsole("######################### GL_");
	//	Er->WriteToConsole(error.c_str());
	//	Er->WriteToConsole(" #########################\n");
	//	err = glGetError();
	//}
}