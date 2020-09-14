#include "EnginePCH.h"
#include "Shader.h"
#include "Engine.h"

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

	void Shader::BindShaderStructure()
	{
		for (ShaderBinding p : bindings)
		{
			if (p.location_type == SHADER_TYPES::ATRIBLOCATION) {
				Engine::getRenderer().VertexStructurePointerF(p.index, p.size, p.normalized, p.packagesize, p.offset);
			}
		}
	}
}