#ifndef _OPENGL_SHADER_H_
#define	_OPENGL_SHADER_H_

#include "Shader.h"

namespace GameEngine 
{
	class OpenGLShader : public Shader 
	{
		public:
			OpenGLShader();
			virtual ~OpenGLShader();
			
			virtual void init(std::string vsFile, std::string fsFile) override; // Initialize our shader file if we have to
						
			virtual void bind() override; // Bind our shader program
			virtual void unbind() override; // Unbind our shader program

			virtual void LinkShader() override;
			unsigned int SortLocation(ShaderBinding item) override;

			void validateShader(GLuint shader, const char* file = 0);
			void validateProgram(GLuint program);
	};

}
#endif