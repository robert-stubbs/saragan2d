#include "EnginePCH.h"
#include "Object.h"


namespace GameEngine
{
	Object::Object()
	{
		isLoaded = false;
	}

	Object::~Object()
	{
		CleanUp();
	}

	void Object::Init()
	{
		isLoaded = true;
	}

	void Object::Update(float dt)
	{
		if (!isLoaded) return;

		hasUpdate = true;
	}

	bool Object::Render()
	{
		if (!isLoaded) return false;

		if (hasUpdate)
		{
			hasUpdate = false;
		}

		return true;
	}

	void Object::CleanUp()
	{

	}
}