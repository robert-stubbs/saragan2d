#ifndef _LINE_H_
#define _LINE_H_

#include "Object.h"


class Line : public Object
{
public:
	Line();
	~Line();
	virtual void Init();
	virtual void Init(float x, float y, float x2, float y2, float z = 0, glm::vec4 colour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	virtual void Init(float x, float y, float angle);

	virtual void UpdatePos(float x, float y, std::vector<Line> hittest);

	virtual void Update(float dt);
	virtual bool Render();
	virtual void CleanUp();

	bool IntersectsLine(Line* line, vert& result);

	GLuint		VAOID[1];
	GLuint		vertexBuffer;
	std::vector<vert> Buffer;

	glm::vec4 colour;
	glm::vec4 mouseLineColour;

	glm::vec3 origin;
	glm::vec3 direction;
	float angle;
	bool mouseLine;
};

#endif