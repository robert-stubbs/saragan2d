#include "EnginePCH.h"
#include "Shader.h"

namespace GameEngine
{
	Shader::Shader() {
		bindings = std::vector<ShaderBinding>();
		locations = std::map<std::string, unsigned int>();
	}

	Shader::~Shader() {}


	unsigned int Shader::operator[](std::string name)
	{
		return locations[name];
	}

	void Shader::SetupLocations()
	{
		LinkShader();

		for (ShaderBinding p : bindings)
		{
			locations[p.name] =  SortLocation(p);
		}
	}
}