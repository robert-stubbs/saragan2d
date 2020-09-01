#ifndef _DEFAULT_2D_SHADER_H_
#define _DEFAULT_2D_SHADER_H_

#include "ShaderDef.h"
#include "Shader.h"

namespace GameEngine {

	class Default2DShader : public ShaderDef
	{
	public:
		Shader* s;

		Default2DShader();
		Default2DShader(std::string vs, std::string fs);
		virtual ~Default2DShader();

		virtual void SetupShader() override;
		virtual void SetupAttributeLocations() override;
		virtual void SetupUniformLocations() override;

		virtual void BindVertStructure() override;

	};
}

#endif 
