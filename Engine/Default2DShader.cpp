#include "EnginePCH.h"
#include "Default2DShader.h"

#include "Engine.h"
#include "Types.h"
#include "SafeDelete.h"
#include "ShaderManager.h"
#include "Renderer.h"


namespace GameEngine {
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
        s->bindings.push_back({ GameEngine::SHADER_TYPES::ATRIBLOCATION, "in_Position", 0, 4, false, sizeof(vert2D), (GLvoid*)offsetof(vert2D, pos) });
        s->bindings.push_back({ GameEngine::SHADER_TYPES::ATRIBLOCATION, "in_Texture", 1, 2, true, sizeof(vert2D), (GLvoid*)offsetof(vert2D, Text) });
        s->bindings.push_back({ GameEngine::SHADER_TYPES::ATRIBLOCATION, "in_Color", 2, 4, true, sizeof(vert2D), (GLvoid*)offsetof(vert2D, col) });
        s->bindings.push_back({ GameEngine::SHADER_TYPES::ATRIBLOCATION, "in_TextureID", 3, 1, true, sizeof(vert2D), (GLvoid*)offsetof(vert2D, TextIndex) });
    }

    void Default2DShader::SetupUniformLocations()
    {
        s->bindings.push_back({ GameEngine::SHADER_TYPES::UNIFORM, "projectionMatrix", 0, 0, false, 0, 0 });
        s->bindings.push_back({ GameEngine::SHADER_TYPES::UNIFORM, "viewMatrix", 0, 0, false, 0, 0 });
        s->bindings.push_back({ GameEngine::SHADER_TYPES::UNIFORM, "modelMatrix", 0, 0, false, 0, 0 });
        s->bindings.push_back({ GameEngine::SHADER_TYPES::UNIFORM, "is_Text", 0, 0, false, 0, 0 });


    }

    void Default2DShader::BindVertStructure()
    {
        // work on this for settings, we have the bindings for atrib location so shouldnt be difficult to provide the offsets as well
        Shader& sr = *s;

        sr.BindShaderStructure();
        //Engine::getRenderer().VertexStructurePointerF(sr["in_Position"], 4, GL_FALSE, sizeof(vert2D), 0);
        //Engine::getRenderer().VertexStructurePointerF(sr["in_Texture"], 2, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, Text));
        //Engine::getRenderer().VertexStructurePointerF(sr["in_Color"], 4, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, col));
    }
}