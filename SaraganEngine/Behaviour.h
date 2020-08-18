#ifndef _C_BEHAVIOR_H_
#define _C_BEHAVIOR_H_

#include "Entity.h"

class Behaviour
{
public:
	bool isPassive;
	bool isDummy;
	std::string name;
	Entity* Ent;

	Behaviour();
	virtual ~Behaviour() {};

	virtual void Init() = 0;
	virtual void DoEnter() = 0;
	virtual void DoExit() = 0;

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual bool handleMessage(SystemMessage msg) = 0;

};

#endif
