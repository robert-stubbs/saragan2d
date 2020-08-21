#ifndef _SHADER_H_
#define	_SHADER_H_

#include "Types.h"

namespace GameEngine
{
	class Shader
	{
	public:
		Shader();
		virtual ~Shader();

		unsigned int ShaderID = 0;
		unsigned int VertexShader = 0;
		unsigned int FragmentShader = 0;

		std::vector<ShaderBinding> bindings;
		std::map<std::string, unsigned int> locations;

		unsigned int operator[](std::string name);
		
		virtual void init(std::string vsFile, std::string fsFile) = 0; // Initialize our shader file if we have to

		virtual void LinkShader() = 0;
		virtual void SetupLocations();
		virtual unsigned int SortLocation(ShaderBinding item) = 0;

		virtual void bind() = 0; // Bind our shader program
		virtual void unbind() = 0; // Unbind our shader program
	};

}

#endif