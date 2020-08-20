#include "EnginePCH.h"
#include "OpenGLShader.h"
#include "FileManager.h"
#include "Shader.h"
#include "Types.h"

namespace GameEngine 
{
	OpenGLShader::OpenGLShader() : Shader()
	{

	}

	OpenGLShader::~OpenGLShader()
	{
		glDetachShader(ShaderID, FragmentShader); // Detach the fragment shader
		glDetachShader(ShaderID, VertexShader); // Detach the vertex shader

		glDeleteShader(FragmentShader); // Delete the fragment shader
		glDeleteShader(VertexShader); // Delete the vertex shader
		glDeleteProgram(ShaderID); // Delete the shader program
	}
	
#pragma region generic functions

	void OpenGLShader::init(std::string vsFile, std::string fsFile)
	{	
		VertexShader = glCreateShader(GL_VERTEX_SHADER);		// Create a vertex shader
		FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);	// Create a fragment shader
	
		std::string vsText = FileManager::textFileRead(vsFile.c_str()); // Read in the vertex shader
		std::string fsText = FileManager::textFileRead(fsFile.c_str()); // Read in the fragment shader
	
		const char* vertexText = vsText.c_str();
		const char* fragmentText = fsText.c_str();
	
		if (vertexText == NULL || fragmentText == NULL) { // If either the vertex or fragment shader wouldn't load
			return;
		}
	
		glShaderSource(VertexShader, 1, &vertexText, 0); // Set the source for the vertex shader to the loaded text
		glCompileShader(VertexShader); // Compile the vertex shader
		validateShader(VertexShader, vsFile.c_str()); // Validate the vertex shader
	
		glShaderSource(FragmentShader, 1, &fragmentText, 0); // Set the source for the fragment shader to the loaded text
		glCompileShader(FragmentShader); // Compile the fragment shader
		validateShader(FragmentShader, fsFile.c_str()); // Validate the fragment shader
	
		ShaderID = glCreateProgram(); // Create a GLSL program
		glAttachShader(ShaderID, VertexShader); // Attach a vertex shader to the program
		glAttachShader(ShaderID, FragmentShader); // Attach the fragment shader to the program

		SetupLocations();
	}
	
	void OpenGLShader::bind()
	{
		glUseProgram(ShaderID);
	}
	
	void OpenGLShader::unbind()
	{
		glUseProgram(0);
	}

	void OpenGLShader::validateShader(GLuint shader, const char* file)
	{
		GLint compile_ok = GL_FALSE;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_ok);
	
		if (1 == compile_ok)
		{
			const unsigned int BUFFER_SIZE = 512;
			char buffer[BUFFER_SIZE];
			memset(buffer, 0, BUFFER_SIZE);
			GLsizei length = 0;
			glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer); // Ask OpenGL to give us the log associated with the shader
	
			std::string buffed(buffer);
	
			int compareBuffer = buffed.compare("No errors.\n");
	
			if (length > 0 && compareBuffer == 1)
			{
				// If we have any information to display
				std::cout << (buffed).c_str() << std::endl;
			}
		}
	}
	
	void OpenGLShader::validateProgram(GLuint program)
	{
		GLint link_ok = GL_FALSE;
	
		glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
		if (link_ok == 0)
		{
			const unsigned int BUFFER_SIZE = 512;
			char buffer[BUFFER_SIZE];
			memset(buffer, 0, BUFFER_SIZE);
			GLsizei length = 0;
	
			glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer); // Ask OpenGL to give us the log associated with the program
			std::string buffed(buffer);
			int compareBuffer = buffed.compare("No errors.\n");
	
			if (length > 0 && compareBuffer == 1)
			{
				// If we have any information to display
			}
	
			glValidateProgram(program); // Get OpenGL to try validating the program
			GLint status;
			glGetProgramiv(program, GL_VALIDATE_STATUS, &status); // Find out if the shader program validated correctly
			if (status == GL_FALSE)
			{
				// If there was a problem validating
				std::cout << "There was an error validating Program" << std::endl;
			}
		}
	}

#pragma endregion generic functions

	void OpenGLShader::LinkShader()
	{
		glLinkProgram(ShaderID); // Link the vertex and fragment shaders in the program
		validateProgram(ShaderID); // Validate the shader program
	}

	unsigned int OpenGLShader::SortLocation(ShaderBinding item)
	{
		switch (item.location_type)
		{
			case SHADER_TYPES::UNIFORM:
				return glGetUniformLocation(ShaderID, item.name.c_str());
			break;

			case SHADER_TYPES::ATRIBLOCATION:
			{
				glBindAttribLocation(ShaderID, item.index, item.name.c_str());
				return glGetAttribLocation(ShaderID, item.name.c_str());
			}
			break;
			default:
				return -1;
			break;
		}
		return -1;
	}

	//unsigned int OpenGLShader::SortLocation(ShaderProp item)
	//{
	//	switch (item.var_type)
	//	{
	//		case SHADER_VAR_TYPES::INT:
	//			return SortLocationInt(item);
	//			break;
	//		case SHADER_VAR_TYPES::FLOAT:
	//			return SortLocationFloat(item);
	//			break;
	//		case SHADER_VAR_TYPES::VEC2:
	//			return SortLocationVec2(item);
	//			break;
	//		case SHADER_VAR_TYPES::VEC3:
	//			return SortLocationVec3(item);
	//			break;
	//		case SHADER_VAR_TYPES::VEC4:
	//			return SortLocationVec4(item);
	//			break;
	//		case SHADER_VAR_TYPES::MAT4:
	//			return SortLocationMat4(item);
	//			break;
	//		default:
	//			return -1;
	//			break;
	//	}
	//	return -1;
	//}


	//unsigned int SortLocationInt(ShaderProp item)
	//{
	//	if (item.location_type == SHADER_TYPES::UNIFORM) {


	//	} else if (item.location_type == SHADER_TYPES::ATRIBLOCATION) {


	//	}
	//}

	//unsigned int SortLocationFloat(ShaderProp item)
	//{
	//	if (item.location_type == SHADER_TYPES::UNIFORM) {


	//	}
	//	else if (item.location_type == SHADER_TYPES::ATRIBLOCATION) {


	//	}
	//}

	//unsigned int SortLocationVec2(ShaderProp item)
	//{
	//	if (item.location_type == SHADER_TYPES::UNIFORM) {


	//	}
	//	else if (item.location_type == SHADER_TYPES::ATRIBLOCATION) {


	//	}
	//}

	//unsigned int SortLocationVec3(ShaderProp item)
	//{
	//	if (item.location_type == SHADER_TYPES::UNIFORM) {


	//	}
	//	else if (item.location_type == SHADER_TYPES::ATRIBLOCATION) {


	//	}
	//}

	//unsigned int SortLocationVec4(ShaderProp item)
	//{
	//	if (item.location_type == SHADER_TYPES::UNIFORM) {


	//	}
	//	else if (item.location_type == SHADER_TYPES::ATRIBLOCATION) {


	//	}
	//}

	//unsigned int SortLocationMat4(ShaderProp item)
	//{
	//	if (item.location_type == SHADER_TYPES::UNIFORM) {


	//	}
	//	else if (item.location_type == SHADER_TYPES::ATRIBLOCATION) {


	//	}
	//}


}