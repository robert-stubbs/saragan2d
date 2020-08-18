#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Dispatch.h"


class Component;

typedef std::shared_ptr<Component> EntityComponentPtr;
typedef std::vector<EntityComponentPtr> EntityComponentBank;

class Entity
{
public:
	std::string m_type;
	std::string m_handle;
	std::string m_entityname;
	EntityComponentBank m_components;
	EntityComponentBank::iterator iter;

	Entity* Parent;
	std::vector<std::string> children;

	bool hasPosition;
	bool hasCamera;
	bool hasCollision;
	bool hasPhysics;
	bool hasInput;
	bool hasGameData;
	bool hasModel;
	bool hasAnimModel;
	bool hasSound;
	bool hasSprite;
	bool hasBrain;

	Entity();
	~Entity();

	//#############################################################
	// Adding Base Components
	//#############################################################
	virtual bool hasComponent(std::string CompName);
	virtual Component* getComponent(std::string CompName);
	virtual void addComponent(Component* comp);

	virtual bool handleMessage(SystemMessage msg) = 0;
};

#endif

