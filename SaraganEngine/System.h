#ifndef _SYSTEM_H_
#define _SYSTEM_H_

class Component;

typedef std::shared_ptr<Component> ComponentPtr;
typedef std::vector<ComponentPtr> ComponentBank;
typedef std::map<std::string, ComponentPtr> ComponentMapBank;

class System
{
public:
	std::string SystemName;

	ComponentBank m_components;
	ComponentBank::iterator iter;

	ComponentMapBank map_components;
	ComponentMapBank::iterator mapiter;

	bool isUI;
	bool isAnim;

	System(bool isui = false, bool isanim = false);
	virtual ~System() {};

	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void RenderAnim() = 0;
	virtual void RenderUI() = 0;

	virtual void CleanUp() = 0;

	virtual void RemoveComponent(std::string handle) = 0;
	virtual Component* getComponent(std::string handle) = 0;

	virtual void AddComponent(std::string handle);
	virtual void AddComponentObject(Component* comp);

private:

};


#endif