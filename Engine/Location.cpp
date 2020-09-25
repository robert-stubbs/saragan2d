#include "EnginePCH.h"
#include "Location.h"

#include "cErrorLogger.h"

namespace GameEngine {

	Location::Location()
	{
		m_type = "LOCATION";
		pos.x = 0.0f;
		pos.y = 0.0f;
		pos.z = 0.0f;
	}

	Location::~Location()
	{
		if (e) {
			e = nullptr;
		}
	}

	bool Location::Init()
	{
		return true;
	}

	void Location::Update(float dt)
	{

	}

	glm::vec3& Location::getPosition()
	{
		return pos;
	}

	glm::mat4 Location::getPositionMat()
	{
		return glm::translate(glm::mat4(1.0f), pos);
	}

	void Location::setPosition(float m_x, float m_y, float m_z)
	{
		pos.x = m_x;
		pos.y = m_y;
		pos.z = m_z;
	}

	void Location::CleanUp()
	{

	}

}