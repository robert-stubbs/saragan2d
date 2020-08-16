#ifndef _SHADER_H_
#define	_SHADER_H_

class Shader
{
public:
	Shader();
	virtual ~Shader();

	bool isAnimShader;
	bool active;

	virtual void init(std::string vsFile, std::string fsFile) = 0; // Initialize our shader file if we have to

	virtual bool bind3dElements() = 0;
	virtual bool bindAnimElements() = 0;


	virtual void bind() = 0; // Bind our shader program
	virtual void unbind() = 0; // Unbind our shader program

	virtual std::string textFileRead(const char* fileName) = 0;
};



#endif