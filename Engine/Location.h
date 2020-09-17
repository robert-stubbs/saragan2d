#ifndef _LOCATION_H_
#define _LOCATION_H_

#include "Types.h"
#include "Component.h"

namespace GameEngine {

	class Location : public Component {
	private:
		float x;
		float y;
		float z;



	public:
		Location();
		virtual ~Location();

		virtual bool Init() override;

		virtual void Update(float dt) override;

		virtual void Render() {};

		virtual void CleanUp() override;

		virtual glm::vec3 getPosition();
		virtual glm::mat4 getPositionMat();
		virtual void setPosition(float m_x, float m_y, float m_z);

	};

}

#endif