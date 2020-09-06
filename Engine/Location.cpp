#include "EnginePCH.h"
#include "Location.h"

#include "cErrorLogger.h"

namespace GameEngine {

	Location::Location()
	{
		m_type = "LOCATION";
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Location::~Location()
	{

	}

	bool Location::Init()
	{
		return true;
	}

	void Location::Update(float dt)
	{

	}

	glm::vec3 Location::getPosition()
	{
		return glm::vec3({ x, y, x });
	}

	glm::mat4 Location::getPositionMat()
	{
		return glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	}

	void Location::setPosition(float m_x, float m_y, float m_z)
	{
		x = m_x;
		y = m_y;
		z = m_z;
	}

	void Location::CleanUp()
	{

	}

}