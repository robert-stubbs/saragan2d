#include "EnginePCH.h"
#include "OpenGLRenderEngine.h"


namespace GameEngine {

	OpenGLRenderEngine::OpenGLRenderEngine()
	{

	}

	OpenGLRenderEngine::~OpenGLRenderEngine()
	{

	}

	bool OpenGLRenderEngine::Init()
	{
		glewExperimental = TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Error Loading Glew" << std::endl;
		}

		std::cout << glGetString(GL_VERSION) << std::endl;

		return true;
	}

	bool OpenGLRenderEngine::PostInit()
	{
		CheckError();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0f);

		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

		glShadeModel(GL_SMOOTH);

		return true;
	}

	void OpenGLRenderEngine::RenderStart()
	{
		// should be moved to the renderer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0f);



	}

	bool OpenGLRenderEngine::Cleanup()
	{
		return true;
	}

	void OpenGLRenderEngine::CheckError()
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

			std::cout << error << std::endl;
		}
	}

	glm::vec3 OpenGLRenderEngine::GetWorldPos(int x, int y, glm::mat4 projection, glm::mat4 view)
	{
		GLint viewport[4];
		GLfloat winY, z;
		glGetIntegerv(GL_VIEWPORT, viewport);

		winY = (GLfloat)((viewport[1] + viewport[3]) - y);

		glReadPixels((GLint)x, (GLint)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);

		return glm::unProject(glm::vec3((double)x, (double)winY, (double)z), view, projection, glm::vec4(viewport[0], viewport[1], viewport[2], viewport[3]));
	}

	glm::vec3 OpenGLRenderEngine::GetWorldPos2D(int x, int y, glm::mat4 projection, glm::mat4 view)
	{
		GLint viewport[4];
		GLfloat winY;
		glGetIntegerv(GL_VIEWPORT, viewport);

		winY = (GLfloat)((viewport[1] + viewport[3]) - y);

		return glm::unProject(glm::vec3((double)x, (double)winY, 0.0f), view, projection, glm::vec4(viewport[0], viewport[1], viewport[2], viewport[3]));
	}

	bool OpenGLRenderEngine::ResizeWindow(int Width, int Height)
	{
		if (Height == 0)
		{
			Height = 1;
		}

		glViewport(0, 0, Width, Height);

		return true;
	}

	void OpenGLRenderEngine::GenerateBuffer(unsigned int& VBO, std::vector<vert>& verts)
	{
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vert) * verts.size(), &verts[0], GL_STATIC_DRAW);

	}

	void OpenGLRenderEngine::ReGenerateBuffer(unsigned int& VBO, std::vector<vert>& verts)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vert) * verts.size(), &verts[0], GL_STATIC_DRAW);
	}

	bool OpenGLRenderEngine::UpdateBuffer(unsigned int& VBO, std::vector<vert>& verts)
	{
		if (VBO != -1)
		{
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vert) * (int)verts.size(), &verts[0]);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			return true;
		}

		return false;
	}

	void OpenGLRenderEngine::BindVertexBuffer(unsigned int& VBO)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	}

	void OpenGLRenderEngine::UnbindVertexBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLRenderEngine::GenerateIndexBuffer(unsigned& IBO, std::vector<int>& VertIndex)
	{
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * VertIndex.size(), &VertIndex[0], GL_STATIC_DRAW);
	}

	void OpenGLRenderEngine::BindIndexBuffer(unsigned int& IBO)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	}
		
	void OpenGLRenderEngine::UnbindIndexBuffer()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLRenderEngine::VertexStructurePointerF(int location, int size, bool normalized, int stride, const void* pointer)
	{
		glVertexAttribPointer(location, size, GL_FLOAT, normalized, stride, pointer);
		glEnableVertexAttribArray(location);
	}

	void OpenGLRenderEngine::UniformMat4(int location, glm::mat4& transform, int size, bool transpose)
	{
		glUniformMatrix4fv(location, size, transpose, glm::value_ptr(transform));
	}
}