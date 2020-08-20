#include "EnginePCH.h"
#include "Default2DShader.h"

#include "Engine.h"
#include "Types.h"
#include "SafeDelete.h"
#include "ShaderManager.h"

Default2DShader::Default2DShader() : ShaderDef()
{
    s = nullptr;
}

Default2DShader::Default2DShader(std::string vs, std::string fs) : ShaderDef(vs, fs)
{
    s = nullptr;
}

Default2DShader::~Default2DShader()
{
}

void Default2DShader::SetupShader()
{
    s = &(GameEngine::Engine::getShader().CreateShaderSpace("DEFAULT2D"));
    SetupAttributeLocations();
    SetupUniformLocations();
    s->init(vs_path, fs_path);
}

void Default2DShader::SetupAttributeLocations()
{
    s->bindings.push_back({ GameEngine::SHADER_TYPES::ATRIBLOCATION, "in_Position", 0 });
    s->bindings.push_back({ GameEngine::SHADER_TYPES::ATRIBLOCATION, "in_Texture", 1 });
    s->bindings.push_back({ GameEngine::SHADER_TYPES::ATRIBLOCATION, "in_Color", 2 });
}

void Default2DShader::SetupUniformLocations()
{
    s->bindings.push_back({ GameEngine::SHADER_TYPES::UNIFORM, "projectionMatrix", 0 });
    s->bindings.push_back({ GameEngine::SHADER_TYPES::UNIFORM, "viewMatrix", 0 });
    s->bindings.push_back({ GameEngine::SHADER_TYPES::UNIFORM, "modelMatrix", 0 });
    s->bindings.push_back({ GameEngine::SHADER_TYPES::UNIFORM, "is_Text", 0 });
}