
#ifndef _LABEL_ENTITY_H_
#define _LABEL_ENTITY_H_ 

#include "Entity.h"


class LabelEntity : public Entity
{
public:

	LabelEntity();
	~LabelEntity();

	virtual void InitWithPositionAndText(float x, float y, std::string text);
	virtual void UpdateLabel(std::string text);

	//virtual bool handleMessage(SystemMessage msg);
};

#endif

