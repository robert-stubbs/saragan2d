#ifndef _COMPONENT_H_
#define _COMPONENT_H_

class Component
{
public:
	std::string m_handle;
	std::string m_type;

	Component();
	virtual ~Component();

	virtual bool Init() = 0;

	virtual void Update(float dt) = 0;

	virtual void Render() = 0;
	virtual void RenderAnim() = 0;
	virtual void RenderUI() = 0;

	virtual void CleanUp() = 0;
};

#endif