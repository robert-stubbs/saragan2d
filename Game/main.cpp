#include "GamePCH.h"
#include "OpenGLShader.h"
#include "Shader.h"

#include "Engine.h"

using namespace GameEngine;

//
//Shader* shader; // Our GLSL shader 
//
//
//typedef struct
//{
//    float  pos[4];
//    float  Text[2];
//} vert;
//
//std::vector<vert> verts = std::vector<vert>();
//
//unsigned int		VAIO;
//unsigned int        VBO;

void PreLoad();
void Load();
void PostLoad();
void Update(float dt);
void Render();
void CleanUp();

int main(void)
{
    PreLoad();
    Load();
    PostLoad();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(Engine::get().window))
    {
        Update(0);
        Render();

    }

    CleanUp();
    return 0;
}

void PreLoad()
{
    Engine& e = Engine::get();

    e.SetAssetDir("C:/Assets/");
    e.SetWindowName("Saragan");
    e.SetWindowSize(800, 600);
    e.PreInit();  
    
    // After Engine Pre Initialisation should be done here


}
void Load()
{
    Engine::get().Init();

    // After Engine Initialisation should be done here
}

void PostLoad()
{
    Engine::get().PostInit();

    // After Engine Post Initialisation should be done here
    
    //shader = new OpenGLShader();
    //shader->init(asset_dir + "Shaders/VertexShader.glsl", asset_dir + "Shaders/FragmentShader.glsl");

    //shader->bind();

    //std::cout << glGetString(GL_VERSION) << std::endl;

    //verts.push_back({ {-0.5f, -0.5f,0.0f,1.0f},{-99.0f,-99.0f} });
    //verts.push_back({ {0.0f, 0.5f,0.0f,1.0f},{-99.0f,-99.0f} });
    //verts.push_back({ {0.5f, -0.5f,0.0f,1.0f},{-99.0f,-99.0f} });


    //glGenVertexArrays(1, &VAIO);
    //glBindVertexArray(VAIO);

    //glGenBuffers(1, &VBO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vert) * verts.size(), &verts[0], GL_STATIC_DRAW);

    //glVertexAttribPointer(shader->Position, 4, GL_FLOAT, GL_FALSE, sizeof(vert), 0);
    //glVertexAttribPointer(shader->Texture, 2, GL_FLOAT, GL_TRUE, sizeof(vert), (GLvoid*)offsetof(vert, Text));

    //glEnableVertexAttribArray(shader->Position);
    //glEnableVertexAttribArray(shader->Texture);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);
}

void Update(float dt)
{
    // put this in its own function in case you want to do 
    // your own updates outside of the engine
    Engine::get().Update(dt);
}

void Render()
{
    // put this in its own function in case you want to do 
    // your own renders outside of the engine
    Engine::get().Render();

    //glUniform1i(shader->isText, 0);

    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_BLEND);

    //glBindVertexArray(VAIO); // Bind our Vertex Array Object
    //glm::vec4 colour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

    //glUniform4fv(shader->Color, 1, glm::value_ptr(colour));

    //glDrawArrays(GL_TRIANGLES, 0, (GLsizei)verts.size()); // Draw our line
    //glDrawArrays(GL_TRIANGLES, 0, (GLsizei)verts.size()); // Draw our line

    //glBindVertexArray(0); // Unbind our Vertex Array Object

    //glDisable(GL_BLEND);

}

void CleanUp()
{
    //Clean up anything you have created prior to this line
    Engine::get().Cleanup();
}

