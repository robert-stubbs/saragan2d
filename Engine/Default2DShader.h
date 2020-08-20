#ifndef _DEFAULT_2D_SHADER_H_
#define _DEFAULT_2D_SHADER_H_

#include "ShaderDef.h"
#include "Shader.h"

class Default2DShader: public ShaderDef
{
public:
	GameEngine::Shader* s;

	Default2DShader();
	Default2DShader(std::string vs, std::string fs);
	virtual ~Default2DShader();

	virtual void SetupShader() override;
	virtual void SetupAttributeLocations() override;
	virtual void SetupUniformLocations() override;

};



#endif 
