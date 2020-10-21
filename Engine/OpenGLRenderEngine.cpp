#include "EnginePCH.h"
#include "OpenGLRenderEngine.h"
#include "Engine.h"


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
			LOG("Error Loading Glew");
		}

		std::string* s = (std::string*)glGetString(GL_VERSION);
		LOG(s->c_str());

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

		CheckError();

		return true;
	}

	void OpenGLRenderEngine::RenderStart()
	{
		// should be moved to the renderer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//glClearDepth(1.0f);
	}

	void OpenGLRenderEngine::SetCurrentContext(HGLRC hRC, HDC hDC)
	{
		HGLRC tempOpenGLContext;

		if (!(tempOpenGLContext = wglCreateContext(hDC)))
		{
			LOG("#### Can't Create A GL Rendering Context ####");
			return;
		}


		if (!wglMakeCurrent(hDC, tempOpenGLContext))
		{
			LOG("#### Can't Activate The GL Rendering Context ####");
			return;
		}

		int attributes[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4, // Set the MAJOR version of OpenGL to 4
			WGL_CONTEXT_MINOR_VERSION_ARB, 4, // Set the MINOR version of OpenGL to 4
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, // Set our OpenGL context to be forward compatible
			0
		};

		glewExperimental = TRUE;
		if (glewInit() != GLEW_OK)
		{
			LOG("#### Error Loading Glew ####");
		}

		std::string* s = (std::string*)glGetString(GL_VERSION);
		LOG(s->c_str());

		if (wglewIsSupported("WGL_ARB_create_context") == 1) { // If the OpenGL 3.x context creation extension is available

			hRC = wglCreateContextAttribsARB(hDC, NULL, attributes); // Create and OpenGL 3.x context based on the given attributes
			wglMakeCurrent(NULL, NULL); // Remove the temporary context from being active
			wglDeleteContext(tempOpenGLContext); // Delete the temporary OpenGL 2.1 context			
			if (!wglMakeCurrent(hDC, hRC))
			{
				LOG("#### Can't Activate The GL Rendering Context ####");
				return;
			}
		}
		else {
			hRC = tempOpenGLContext; // If we didn't have support for OpenGL 3.x and up, use the OpenGL 2.1 context

		}

		int Major = 0;
		int Minor = 0;

		glGetIntegerv(GL_MAJOR_VERSION, &Major); // major = 3
		glGetIntegerv(GL_MINOR_VERSION, &Minor); // minor = 2

		LOG("OpenGL Version " + std::to_string(Major) + " " + std::to_string(Minor));
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

			LOG(error);
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

		// resize GUI
		if (Engine::get().loaded) {
			Engine::get().SetWindowSize(Width, Height);
			Engine::getGUI().ResizeWindow(Width, Height);
		}
		return true;
	}

	void OpenGLRenderEngine::GenerateVertexArrayBuffer(unsigned int& VAO)
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
	}

	void OpenGLRenderEngine::DeleteVertexBuffer(unsigned int& VAO)
	{
		glDeleteVertexArrays(1, &VAO);
	}

	void OpenGLRenderEngine::DeleteBuffer(unsigned int& VAO)
	{
		glDeleteBuffers(1, &VAO);
	}

	void OpenGLRenderEngine::GenerateBuffer(unsigned int& VBO, std::vector<vert>& verts)
	{
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vert) * verts.size(), &verts[0], GL_STATIC_DRAW);

	}

	void OpenGLRenderEngine::GenerateBuffer(unsigned int& VBO, std::vector<vert2D>& verts)
	{
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vert2D) * verts.size(), &verts[0], GL_STATIC_DRAW);
	}

	void OpenGLRenderEngine::GenerateEmptyBuffer(unsigned int& VBO, int size)
	{
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	void OpenGLRenderEngine::ReGenerateBuffer(unsigned int& VBO, std::vector<vert>& verts)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vert) * verts.size(), &verts[0], GL_STATIC_DRAW);
	}

	void OpenGLRenderEngine::ReGenerateBuffer(unsigned int& VBO, std::vector<vert2D>& verts)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vert2D) * verts.size(), &verts[0], GL_STATIC_DRAW);
	}

	void OpenGLRenderEngine::BufferSubData(unsigned int& VBO, std::vector<vert2D>& verts)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vert2D) * verts.size(), &verts[0]);
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

	bool OpenGLRenderEngine::UpdateBuffer(unsigned int& VBO, std::vector<vert2D>& verts)
	{
		if (VBO != -1)
		{
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vert2D) * (int)verts.size(), &verts[0]);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			return true;
		}

		return false;
	}

	void OpenGLRenderEngine::BindVertexBuffer(unsigned int& VAO)
	{
		glBindVertexArray(VAO);
	}

	void OpenGLRenderEngine::UnbindVertexBuffer()
	{
		glBindVertexArray(0);
	}

	void OpenGLRenderEngine::BindBuffer(unsigned int& VBO)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	}

	void OpenGLRenderEngine::UnbindBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLRenderEngine::GenerateIndexBuffer(unsigned int& IBO, std::vector<int>& VertIndex)
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

	void OpenGLRenderEngine::GenerateTextureBuffer(unsigned int& TBO, int width, int height, void* data, COLOR_TYPE internalformat, COLOR_TYPE format, VALUE_TYPE type)
	{
		int t = GL_UNSIGNED_BYTE;
		switch (type)
		{
		case GameEngine::VALUE_TYPE::UNSIGNED_BYTE:
			t = GL_UNSIGNED_BYTE;
			break;
		case GameEngine::VALUE_TYPE::UNSIGNED_SHORT:
			t = GL_UNSIGNED_SHORT;
			break;
		case GameEngine::VALUE_TYPE::UNSIGNED_INT:
			t = GL_UNSIGNED_INT;
			break;
		default:
			break;
		}

		int iformat = GL_RGB;

		switch (internalformat)
		{
		case GameEngine::COLOR_TYPE::ENGINE_RED:
			iformat = GL_RED;
			break;
		case GameEngine::COLOR_TYPE::ENGINE_GREEN:
			iformat = GL_GREEN;
			break;
		case GameEngine::COLOR_TYPE::ENGINE_BLUE:
			iformat = GL_BLUE;
			break;
		case GameEngine::COLOR_TYPE::ENGINE_RGB:
			iformat = GL_RGB;
			break;
		case GameEngine::COLOR_TYPE::ENGINE_RGBA:
			iformat = GL_RGBA;
			break;
		default:
			break;
		}

		int form = GL_RGB;

		switch (format)
		{
		case GameEngine::COLOR_TYPE::ENGINE_RED:
			form = GL_RED;
			break;
		case GameEngine::COLOR_TYPE::ENGINE_GREEN:
			form = GL_GREEN;
			break;
		case GameEngine::COLOR_TYPE::ENGINE_BLUE:
			form = GL_BLUE;
			break;
		case GameEngine::COLOR_TYPE::ENGINE_RGB:
			form = GL_RGB;
			break;
		case GameEngine::COLOR_TYPE::ENGINE_RGBA:
			form = GL_RGBA;
			break;
		default:
			break;
		}


		glGenTextures(1, &TBO);
		glBindTexture(GL_TEXTURE_2D, TBO);
		glTexImage2D(GL_TEXTURE_2D, 0, iformat, width, height, 0, form, t, data);
	}

	void OpenGLRenderEngine::BindTextureBuffer(unsigned int& TBO)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TBO);
	}
	
	void OpenGLRenderEngine::BindTextureBufferParams(TEXTURE_TARGET target, TEXTURE_TARGET_NAME name, TEXTURE_TARGET_PARAM param)
	{
		unsigned int t = GL_TEXTURE_2D;

		switch (target)
		{
		case TEXTURE_TARGET::ENGINE_TEXTURE_2D:
			t = GL_TEXTURE_2D;
			break;
		default:
			break;
		}

		unsigned int n = GL_TEXTURE_MAG_FILTER;

		switch (name)
		{
		case TEXTURE_TARGET_NAME::ENGINE_TEXTURE_MAG_FILTER:
			n = GL_TEXTURE_MAG_FILTER;
			break;
		case TEXTURE_TARGET_NAME::ENGINE_TEXTURE_MIN_FILTER:
			n = GL_TEXTURE_MIN_FILTER;
			break;
		case TEXTURE_TARGET_NAME::ENGINE_TEXTURE_WRAP_S:
			n = GL_TEXTURE_WRAP_S;
			break;
		case TEXTURE_TARGET_NAME::ENGINE_TEXTURE_WRAP_T:
			n = GL_TEXTURE_WRAP_T;
			break;
		default:
			break;
		}

		unsigned int p = GL_LINEAR;

		switch (param)
		{
		case TEXTURE_TARGET_PARAM::ENGINE_CLAMP_TO_EDGE:
			p = GL_CLAMP_TO_EDGE;
			break;
		case TEXTURE_TARGET_PARAM::ENGINE_LINEAR:
			p = GL_LINEAR;
			break;
		case TEXTURE_TARGET_PARAM::ENGINE_NEAREST:
			p = GL_NEAREST;
			break;
		case TEXTURE_TARGET_PARAM::ENGINE_LINEAR_MIPMAP_LINEAR:
			p = GL_LINEAR_MIPMAP_LINEAR;
			break;
		default:
			break;
		}



		glTexParameteri(t, n, p);
	}

	void OpenGLRenderEngine::GenerateTextureMipmap()
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void OpenGLRenderEngine::UnbindTextureBuffer()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	// Frame buffer
	void OpenGLRenderEngine::GenerateFrameBuffer(unsigned int& FBO)
	{
		glGenFramebuffers(1, &FBO);
		BindFrameBuffer(FBO);
	}

	void OpenGLRenderEngine::BindFrameBuffer(unsigned int& FBO)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	}

	void OpenGLRenderEngine::UnbindFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLRenderEngine::DeleteFrameBuffer(unsigned int& FBO)
	{
		glDeleteFramebuffers(1, &FBO);
	}

	bool OpenGLRenderEngine::FrameBufferComplete()
	{
		bool is_complete = (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

		if (!is_complete) {
			LOG("Frame Buffer is not complete");
		}

		return is_complete;
	}

	void OpenGLRenderEngine::GenerateFrameBufferTexture(unsigned int& TextureID)
	{
		glGenTextures(1, &TextureID);
		glBindTexture(GL_TEXTURE_2D, TextureID);

		float width = Engine::get().RenderWidth;
		float height = Engine::get().RenderHeight;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei)width, (GLsizei)height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void OpenGLRenderEngine::BindTextureToFrameBuffer(unsigned int& TextureID)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TextureID, 0);

		GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
	}

	void OpenGLRenderEngine::VertexStructurePointerF(int location, int size, bool normalized, int stride, const void* pointer)
	{
		glVertexAttribPointer(location, size, GL_FLOAT, normalized, stride, pointer);
		glEnableVertexAttribArray(location);
		CheckError();
	}

	void OpenGLRenderEngine::UniformInt(int location, int value)
	{
		glUniform1i(location, value);
	}

	void OpenGLRenderEngine::UniformVec4(int location, glm::vec4& vector, int count)
	{
		glUniform4fv(location, count, glm::value_ptr(vector));
	}

	void OpenGLRenderEngine::UniformMat4(int location, glm::mat4& transform, int size, bool transpose)
	{
		glUniformMatrix4fv(location, size, transpose, glm::value_ptr(transform));
	}

	void OpenGLRenderEngine::EnableBlend(bool enabled, BLEND_TYPE sfactor, BLEND_TYPE dfactor)
	{
		if (!enabled) {
			glDisable(GL_BLEND);
			return;
		}

		GLenum sfact;
		GLenum dfact;

		switch (sfactor)
		{
		case BLEND_TYPE::SRC_COLOR:
			sfact = GL_SRC_COLOR;
			break;
		case BLEND_TYPE::ONE_MINUS_SRC_COLOR:
			sfact = GL_ONE_MINUS_SRC_COLOR;
			break;
		case BLEND_TYPE::SRC_ALPHA:
			sfact = GL_SRC_ALPHA;
			break;
		case BLEND_TYPE::ONE_MINUS_SRC_ALPHA:
			sfact = GL_ONE_MINUS_SRC_ALPHA;
			break;
		case BLEND_TYPE::DST_ALPHA:
			sfact = GL_DST_ALPHA;
			break;
		case BLEND_TYPE::ONE_MINUS_DST_ALPHA:
			sfact = GL_ONE_MINUS_DST_ALPHA;
			break;
		case BLEND_TYPE::DST_COLOR:
			sfact = GL_DST_COLOR;
			break;
		case BLEND_TYPE::ONE_MINUS_DST_COLOR:
			sfact = GL_ONE_MINUS_DST_COLOR;
			break;
		case BLEND_TYPE::SRC_ALPHA_SATURATE:
			sfact = GL_SRC_ALPHA_SATURATE;
			break;
		default:
			sfact = GL_SRC_ALPHA;
			break;
		}

		switch (dfactor)
		{
			case BLEND_TYPE::SRC_COLOR:
				dfact = GL_SRC_COLOR;
				break;
			case BLEND_TYPE::ONE_MINUS_SRC_COLOR:
				dfact = GL_ONE_MINUS_SRC_COLOR;
				break;
			case BLEND_TYPE::SRC_ALPHA:
				dfact = GL_SRC_ALPHA;
				break;
			case BLEND_TYPE::ONE_MINUS_SRC_ALPHA:
				dfact = GL_ONE_MINUS_SRC_ALPHA;
				break;
			case BLEND_TYPE::DST_ALPHA:
				dfact = GL_DST_ALPHA;
				break;
			case BLEND_TYPE::ONE_MINUS_DST_ALPHA:
				dfact = GL_ONE_MINUS_DST_ALPHA;
				break;
			case BLEND_TYPE::DST_COLOR:
				dfact = GL_DST_COLOR;
				break;
			case BLEND_TYPE::ONE_MINUS_DST_COLOR:
				dfact = GL_ONE_MINUS_DST_COLOR;
				break;
			case BLEND_TYPE::SRC_ALPHA_SATURATE:
				dfact = GL_SRC_ALPHA_SATURATE;
				break;
			default:
				dfact = GL_ONE_MINUS_SRC_ALPHA;
				break;
		}

		glBlendFunc(sfact, dfact);
		glEnable(GL_BLEND);
	}

	void OpenGLRenderEngine::EnableDepthTest(bool enabled)
	{
		if (enabled)
		{
			glEnable(GL_DEPTH_TEST);
			return;
		}

		glDisable(GL_DEPTH_TEST);
	}

	

	void OpenGLRenderEngine::DrawArrays(DRAW_TYPE type, int count, int first)
	{
		GLenum val;

		switch (type)
		{
		case DRAW_TYPE::LINE:
			val = GL_LINE;
			break;
		case DRAW_TYPE::LINES:
			val = GL_LINES;
			break;
		case DRAW_TYPE::LINE_LOOP:
			val = GL_LINE_LOOP;
			break;
		case DRAW_TYPE::LINE_STRIP:
			val = GL_LINE_STRIP;
			break;
		case DRAW_TYPE::TRIANGLES:
			val = GL_TRIANGLES;
			break;
		case DRAW_TYPE::TRIANGLE_STRIP:
			val = GL_TRIANGLE_STRIP;
			break;
		case DRAW_TYPE::TRIANGLE_FAN:
			val = GL_TRIANGLE_FAN;
			break;
		case DRAW_TYPE::QUADS:
			val = GL_QUADS;
			break;
		case DRAW_TYPE::QUAD_STRIP:
			val = GL_QUAD_STRIP;
			break;
		default:
			val = GL_LINES;
			break;
		}

		glDrawArrays(val, first, count);
	}

	void OpenGLRenderEngine::DrawElements(DRAW_TYPE type, int count, VALUE_TYPE indice_type, void* offset)
	{
		GLenum val;
		GLenum ind;


		switch (type)
		{
		case DRAW_TYPE::LINES:
			val = GL_LINES;
			break;
		case DRAW_TYPE::LINE_LOOP:
			val = GL_LINE_LOOP;
			break;
		case DRAW_TYPE::LINE_STRIP:
			val = GL_LINE_STRIP;
			break;
		case DRAW_TYPE::TRIANGLES:
			val = GL_TRIANGLES;
			break;
		case DRAW_TYPE::TRIANGLE_STRIP:
			val = GL_TRIANGLE_STRIP;
			break;
		case DRAW_TYPE::TRIANGLE_FAN:
			val = GL_TRIANGLE_FAN;
			break;
		case DRAW_TYPE::QUADS:
			val = GL_QUADS;
			break;
		case DRAW_TYPE::QUAD_STRIP:
			val = GL_QUAD_STRIP;
			break;
		default:
			val = GL_LINES;
			break;
		}

		switch (indice_type)
		{
		case VALUE_TYPE::UNSIGNED_BYTE:
			ind = GL_UNSIGNED_BYTE;
			break;
		case VALUE_TYPE::UNSIGNED_SHORT:
			ind = GL_UNSIGNED_SHORT;
			break;
		case VALUE_TYPE::UNSIGNED_INT:
			ind = GL_UNSIGNED_INT;
			break;
		default:
			break;
		}

		glDrawElements(val, count, ind, offset);
	}

	void OpenGLRenderEngine::DrawIntElements(DRAW_TYPE type, int count, int offset)
	{
		GLenum val;

		switch (type)
		{
		case DRAW_TYPE::LINES:
			val = GL_LINES;
			break;
		case DRAW_TYPE::LINE_LOOP:
			val = GL_LINE_LOOP;
			break;
		case DRAW_TYPE::LINE_STRIP:
			val = GL_LINE_STRIP;
			break;
		case DRAW_TYPE::TRIANGLES:
			val = GL_TRIANGLES;
			break;
		case DRAW_TYPE::TRIANGLE_STRIP:
			val = GL_TRIANGLE_STRIP;
			break;
		case DRAW_TYPE::TRIANGLE_FAN:
			val = GL_TRIANGLE_FAN;
			break;
		case DRAW_TYPE::QUADS:
			val = GL_QUADS;
			break;
		case DRAW_TYPE::QUAD_STRIP:
			val = GL_QUAD_STRIP;
			break;
		default:
			val = GL_LINES;
			break;
		}

		glDrawElements(val, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(unsigned int)));
	}

	void OpenGLRenderEngine::DrawByteElements(DRAW_TYPE type, int count, unsigned char offset)
	{
		GLenum val;

		switch (type)
		{
		case DRAW_TYPE::LINES:
			val = GL_LINES;
			break;
		case DRAW_TYPE::LINE_LOOP:
			val = GL_LINE_LOOP;
			break;
		case DRAW_TYPE::LINE_STRIP:
			val = GL_LINE_STRIP;
			break;
		case DRAW_TYPE::TRIANGLES:
			val = GL_TRIANGLES;
			break;
		case DRAW_TYPE::TRIANGLE_STRIP:
			val = GL_TRIANGLE_STRIP;
			break;
		case DRAW_TYPE::TRIANGLE_FAN:
			val = GL_TRIANGLE_FAN;
			break;
		case DRAW_TYPE::QUADS:
			val = GL_QUADS;
			break;
		case DRAW_TYPE::QUAD_STRIP:
			val = GL_QUAD_STRIP;
			break;
		default:
			val = GL_LINES;
			break;
		}

		glDrawElements(val, count, GL_UNSIGNED_BYTE, (void*)(offset * sizeof(unsigned char)));
	}

	void OpenGLRenderEngine::DrawShortElements(DRAW_TYPE type, int count, short offset)
	{
		GLenum val;

		switch (type)
		{
		case DRAW_TYPE::LINES:
			val = GL_LINES;
			break;
		case DRAW_TYPE::LINE_LOOP:
			val = GL_LINE_LOOP;
			break;
		case DRAW_TYPE::LINE_STRIP:
			val = GL_LINE_STRIP;
			break;
		case DRAW_TYPE::TRIANGLES:
			val = GL_TRIANGLES;
			break;
		case DRAW_TYPE::TRIANGLE_STRIP:
			val = GL_TRIANGLE_STRIP;
			break;
		case DRAW_TYPE::TRIANGLE_FAN:
			val = GL_TRIANGLE_FAN;
			break;
		case DRAW_TYPE::QUADS:
			val = GL_QUADS;
			break;
		case DRAW_TYPE::QUAD_STRIP:
			val = GL_QUAD_STRIP;
			break;
		default:
			val = GL_LINES;
			break;
		}

		glDrawElements(val, count, GL_UNSIGNED_SHORT, (void*)(offset * sizeof(unsigned short)));
	}
}