#ifndef _MODEL_SYSTEM_H_
#define _MODEL_SYSTEM_H_

//#include <fbxsdk.h>
//http://help.autodesk.com/view/FBX/2020/ENU/?guid=FBX_Developer_Help_getting_started_your_first_fbx_sdk_program_html

#include "System.h"

namespace GameEngine
{
	class ModelSystem : public System
	{
	public:
		ModelSystem(bool isui = false, bool isanim = false);
		~ModelSystem();

		virtual void Init();
		virtual void Update(float dt);
		virtual void Render();
		virtual void RenderAnim();
		virtual void RenderUI() {};

		virtual void CleanUp();

		virtual void RemoveComponent(std::string handle);
		virtual Component* getComponent(std::string handle);

	};
}

#endif