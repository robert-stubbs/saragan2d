#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Component.h"

namespace GameEngine
{
	enum class CollisionType {
		BOX = 0,
		SPEHERE
	};

	class Collision : public Component {

		private:
			CollisionType _type;

		public:
			Collision();
			virtual ~Collision();

			virtual bool Init() override;

			virtual void Update(float dt) override;

			virtual void Render() {};

			virtual void CleanUp() override;
	};
}

#endif