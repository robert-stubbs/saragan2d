#ifndef _C_GUI_SYSTEM_H_
#define _C_GUI_SYSTEM_H_

#include "System.h"
#include "Font.h"
#include "Text.h"

#include <map>
#include <string>

class GUISystem : public System
{
public:
	GUISystem(bool isui = false, bool isanim = false);
	virtual ~GUISystem();

	std::map<std::string, Font> Fonts;

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render() {};
	virtual void RenderAnim() {};
	virtual void RenderUI();

	virtual void CleanUp();

	virtual void AddFontFile(float fontSize, std::string FontFile, std::string key);
	virtual Font* getFont(std::string name);

	virtual void AddComponent(std::string handle);
	virtual void RemoveComponent(std::string handle);
	virtual Component* getComponent(std::string handle);

	//virtual void AddElemComponent(cUIElement* comp);
};

#endif
