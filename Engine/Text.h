#ifndef _TEXT_H_
#define _TEXT_H_

#include "Component.h"

namespace GameEngine
{
	class Text : public Component
	{
		public:

			Text();
			virtual ~Text();

			virtual bool Init();

			virtual void Update(float dt);

			virtual void Render();

			virtual void CleanUp();
	};
}

#endif