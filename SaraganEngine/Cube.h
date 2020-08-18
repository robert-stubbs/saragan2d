#ifndef _CUBE_H_
#define _CUBE_H_

#include "Object.h"
#include "Texture.h"

/*
	This class is really only intended for 2D
*/
class Cube : public Object
{
public:
	Cube();
	~Cube();
	virtual void Init();
	virtual void Init(float x, float y, float z, float width, float height);

	virtual void GenerateVerts();

	virtual void Update(float dt);
	virtual bool Render();
	virtual void CleanUp();

	bool hasTexture;
	Texture* texture;
	virtual void SetupTexture(std::string path);

	GLuint VAIO;
	GLuint IBO;
	GLuint VBO;

	std::vector<vert> verts;
	std::vector<int> VertIndex;

	glm::vec3 origin;
	float width;
	float height;

	glm::vec4 colour;
};

#endif