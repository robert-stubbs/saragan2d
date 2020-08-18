#include "EnginePCH.h"
#include "Position.h"

#include "cErrorLogger.h"

Position::Position()
{
	m_type = "position";
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Position::~Position()
{

}

bool Position::Init()
{
	cErrorLogger::Er->WriteToConsole("> Initialized Position\n");
	return true;
}

void Position::Update(float dt)
{

}

position Position::getPosition()
{
	return{ x, y, x };
}

glm::mat4 Position::getPositionMat()
{
	return glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void Position::setPosition(float m_x, float m_y, float m_z)
{
	x = m_x;
	y = m_y;
	z = m_z;
}

bool Position::handleMessage(SystemMessage msg)
{
	switch (msg.MessageType)
	{
	case 0:
	{


	} break;
	default:
	{


	}break;

	}

	return false;
}

void Position::CleanUp()
{

}
