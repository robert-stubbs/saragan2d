#ifndef _OPENGL_SHADER_H_
#define	_OPENGL_SHADER_H_

#include "Shader.h"

class OpenGLShader : public Shader {
public:	
	
	  GLuint ShaderID = 0;
	  GLuint VertexShader = 0;
	  GLuint FragmentShader = 0;

	  GLuint Position = 0;
	  GLuint Color = 0;
	  GLuint Texture = 0;
	  GLuint Normal = 0;
	  GLuint UniformMat = 0;

	  GLuint weight = 0;
	  GLuint boneIndex = 0;
	  GLuint boneMatrix = 0;

	  GLuint isText = 0;

	  struct {
		  GLuint Color;
		  GLuint AmbientIntensity;
		  GLuint Direction;
		  GLuint DiffuseIntensity;
		  GLuint isWorldSource;
	  } WorldLight;

	  int projectionMatrixLocation; // Get the location of our projection matrix in the shader  
	  int viewMatrixLocation; // Get the location of our view matrix in the shader  
	  int modelMatrixLocation;


	OpenGLShader();
	virtual ~OpenGLShader();

	virtual void init(std::string vsFile, std::string fsFile) override; // Initialize our shader file if we have to

	virtual bool bind3dElements() override;
	virtual bool bindAnimElements() override;


	virtual void bind() override; // Bind our shader program
	virtual void unbind() override; // Unbind our shader program

	virtual std::string textFileRead(const char* fileName) override;

	void validateShader(GLuint shader, const char* file = 0);
	void validateProgram(GLuint program);

};

#endif