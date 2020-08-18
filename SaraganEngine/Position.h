#ifndef _POSITION_H_
#define _POSITION_H_

#include "Component.h"

typedef struct
{
	float x;
	float y;
	float z;
} position;

class Position : public Component
{
public:
	float x;
	float y;
	float z;

	Position();
	~Position();

	virtual bool Init();

	virtual void Update(float dt);
	virtual void Render() {};
	virtual void RenderAnim() {};
	//virtual bool handleMessage(SystemMessage msg);

	virtual position getPosition();
	virtual glm::mat4 getPositionMat();
	virtual void setPosition(float m_x, float m_y, float m_z);

	virtual void CleanUp();
};

#endif