#include "EnginePCH.h"
#include "OpenGLShader.h"
#include "Shader.h"
//
//OpenGLShader::OpenGLShader() : Shader()
//{
//
//}
//
//OpenGLShader::~OpenGLShader()
//{
//	glDetachShader(ShaderID, FragmentShader); // Detach the fragment shader
//	glDetachShader(ShaderID, VertexShader); // Detach the vertex shader
//
//	glDeleteShader(FragmentShader); // Delete the fragment shader
//	glDeleteShader(VertexShader); // Delete the vertex shader
//	glDeleteProgram(ShaderID); // Delete the shader program
//}
//
//void OpenGLShader::init(std::string vsFile, std::string fsFile)
//{
//	if (active)
//	{
//		return;
//	}
//	active = true;
//
//	VertexShader = glCreateShader(GL_VERTEX_SHADER);		// Create a vertex shader
//	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);	// Create a fragment shader
//
//	std::string vsText = textFileRead(vsFile.c_str()); // Read in the vertex shader
//	std::string fsText = textFileRead(fsFile.c_str()); // Read in the fragment shader
//
//	const char* vertexText = vsText.c_str();
//	const char* fragmentText = fsText.c_str();
//
//	if (vertexText == NULL || fragmentText == NULL) { // If either the vertex or fragment shader wouldn't load
//		return;
//	}
//
//	glShaderSource(VertexShader, 1, &vertexText, 0); // Set the source for the vertex shader to the loaded text
//	glCompileShader(VertexShader); // Compile the vertex shader
//	validateShader(VertexShader, vsFile.c_str()); // Validate the vertex shader
//
//	glShaderSource(FragmentShader, 1, &fragmentText, 0); // Set the source for the fragment shader to the loaded text
//	glCompileShader(FragmentShader); // Compile the fragment shader
//	validateShader(FragmentShader, fsFile.c_str()); // Validate the fragment shader
//
//	ShaderID = glCreateProgram(); // Create a GLSL program
//	glAttachShader(ShaderID, VertexShader); // Attach a vertex shader to the program
//	glAttachShader(ShaderID, FragmentShader); // Attach the fragment shader to the program
//
//	if (isAnimShader)
//	{
//		bindAnimElements();
//	}
//	else {
//		bind3dElements();
//	}
//}
//
//bool OpenGLShader::bind3dElements()
//{
//	glBindAttribLocation(ShaderID, 0, "in_Position"); // Bind a constant attribute location for positions of vertices
//	glBindAttribLocation(ShaderID, 1, "in_Texture"); // Bind another constant attribute location, this time for color
//	glBindAttribLocation(ShaderID, 2, "in_Color"); // Bind another constant attribute location, this time for color
//
//	glLinkProgram(ShaderID); // Link the vertex and fragment shaders in the program
//	validateProgram(ShaderID); // Validate the shader program
//
//	projectionMatrixLocation = glGetUniformLocation(ShaderID, "projectionMatrix"); // Get the location of our projection matrix in the shader
//	viewMatrixLocation = glGetUniformLocation(ShaderID, "viewMatrix"); // Get the location of our view matrix in the shader
//	modelMatrixLocation = glGetUniformLocation(ShaderID, "modelMatrix"); // Get the location of our model matrix in the shader
//
//	//Color = glGetUniformLocation(ShaderID, "in_Color");
//	isText = glGetUniformLocation(ShaderID, "is_Text");
//
//	Position = glGetAttribLocation(ShaderID, "in_Position");
//	Texture = glGetAttribLocation(ShaderID, "in_Texture");
//	Color = glGetAttribLocation(ShaderID, "in_Color");
//
//	WorldLight.Color = glGetUniformLocation(ShaderID, "WorldLight.Color");
//	WorldLight.AmbientIntensity = glGetUniformLocation(ShaderID, "WorldLight.AmbientIntensity");
//	WorldLight.Direction = glGetUniformLocation(ShaderID, "WorldLight.Direction");
//	WorldLight.DiffuseIntensity = glGetUniformLocation(ShaderID, "WorldLight.DiffuseIntensity");
//	WorldLight.isWorldSource = glGetUniformLocation(ShaderID, "WorldLight.isWorldSource");
//
//	return true;
//}
//
//bool OpenGLShader::bindAnimElements()
//{
//	glBindAttribLocation(ShaderID, 0, "in_Position"); // Bind a constant attribute location for positions of vertices
//	glBindAttribLocation(ShaderID, 1, "in_Texture"); // Bind another constant attribute location, this time for color
//	glBindAttribLocation(ShaderID, 2, "in_Norm"); // Bind another constant attribute location, this time for color
//	glBindAttribLocation(ShaderID, 3, "in_Weight"); // Bind another constant attribute location, this time for color
//	glBindAttribLocation(ShaderID, 4, "in_BoneIndex"); // Bind another constant attribute location, this time for color
//
//	glLinkProgram(ShaderID); // Link the vertex and fragment shaders in the program
//	validateProgram(ShaderID); // Validate the shader program
//
//	projectionMatrixLocation = glGetUniformLocation(ShaderID, "projectionMatrix"); // Get the location of our projection matrix in the shader
//	viewMatrixLocation = glGetUniformLocation(ShaderID, "viewMatrix"); // Get the location of our view matrix in the shader
//	modelMatrixLocation = glGetUniformLocation(ShaderID, "modelMatrix"); // Get the location of our model matrix in the shader
//
//	boneMatrix = glGetUniformLocation(ShaderID, "boneMatrix");
//
//	Position = glGetAttribLocation(ShaderID, "in_Position");
//	Texture = glGetAttribLocation(ShaderID, "in_Texture");
//	Normal = glGetAttribLocation(ShaderID, "in_Norm");
//	weight = glGetAttribLocation(ShaderID, "in_Weight");
//	boneIndex = glGetAttribLocation(ShaderID, "in_BoneIndex");
//
//	return true;
//}
//
//void OpenGLShader::bind()
//{
//	glUseProgram(ShaderID);
//}
//
//void OpenGLShader::unbind()
//{
//	glUseProgram(0);
//}
//
//std::string OpenGLShader::textFileRead(const char* fileName)
//{
//	std::string fileString = std::string(); // A string for storing the file contents
//	std::string line = std::string(); // A string for holding the current line
//
//	std::ifstream file(fileName); // Open an input stream with the selected file
//	if (file.is_open()) { // If the file opened successfully
//		while (!file.eof()) { // While we are not at the end of the file
//			getline(file, line); // Get the current line
//			fileString.append(line); // Append the line to our file string
//			fileString.append("\n"); // Appand a new line character
//		}
//		file.close(); // Close the file
//	}
//
//	return fileString; // Return our string
//}
//
//void OpenGLShader::validateShader(GLuint shader, const char* file)
//{
//	GLint compile_ok = GL_FALSE;
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_ok);
//
//	if (1 == compile_ok)
//	{
//		const unsigned int BUFFER_SIZE = 512;
//		char buffer[BUFFER_SIZE];
//		memset(buffer, 0, BUFFER_SIZE);
//		GLsizei length = 0;
//		glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer); // Ask OpenGL to give us the log associated with the shader
//
//		std::string buffed(buffer);
//
//		int compareBuffer = buffed.compare("No errors.\n");
//
//		if (length > 0 && compareBuffer == 1)
//		{
//			// If we have any information to display
//			std::cout << (buffed).c_str() << std::endl;
//		}
//	}
//}
//
//void OpenGLShader::validateProgram(GLuint program)
//{
//	GLint link_ok = GL_FALSE;
//
//	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
//	if (link_ok == 0)
//	{
//		const unsigned int BUFFER_SIZE = 512;
//		char buffer[BUFFER_SIZE];
//		memset(buffer, 0, BUFFER_SIZE);
//		GLsizei length = 0;
//
//		glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer); // Ask OpenGL to give us the log associated with the program
//		std::string buffed(buffer);
//		int compareBuffer = buffed.compare("No errors.\n");
//
//		if (length > 0 && compareBuffer == 1)
//		{
//			// If we have any information to display
//		}
//
//		glValidateProgram(program); // Get OpenGL to try validating the program
//		GLint status;
//		glGetProgramiv(program, GL_VALIDATE_STATUS, &status); // Find out if the shader program validated correctly
//		if (status == GL_FALSE)
//		{
//			// If there was a problem validating
//			std::cout << "There was an error validating Program" << std::endl;
//		}
//	}
//}
