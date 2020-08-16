#ifndef _SHADER_H_
#define	_SHADER_H_

class Shader
{
public:
	Shader();
	virtual ~Shader();

	unsigned int ShaderID = 0;
	unsigned int VertexShader = 0;
	unsigned int FragmentShader = 0;

	unsigned int Position = 0;
	unsigned int Color = 0;
	unsigned int Texture = 0;
	unsigned int Normal = 0;
	unsigned int UniformMat = 0;

	unsigned int weight = 0;
	unsigned int boneIndex = 0;
	unsigned int boneMatrix = 0;

	unsigned int isText = 0;

	int projectionMatrixLocation; // Get the location of our projection matrix in the shader  
	int viewMatrixLocation; // Get the location of our view matrix in the shader  
	int modelMatrixLocation;

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