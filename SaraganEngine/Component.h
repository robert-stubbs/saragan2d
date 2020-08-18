#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Dispatch.h"

class Entity;

class Component
{
public:
	std::string m_handle;
	std::string m_type;
	Entity* ent;

	bool isAnim;
	int renderLevel;

	Component();
	virtual ~Component();

	virtual bool Init() = 0;

	virtual void Update(float dt) = 0;

	virtual void Render() = 0;
	virtual void RenderAnim() = 0;
	virtual void RenderUI() = 0;

	virtual void CleanUp() = 0;
	virtual bool handleMessage(SystemMessage msg) = 0;
};

#endif