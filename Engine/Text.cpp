#include "EnginePCH.h"
#include "Text.h"

namespace GameEngine
{

	Text::Text() : Component()
	{

		m_type = "TEXT";
	}

	Text::~Text()
	{

	}

	bool Text::Init()
	{

		return true;
	}

	void Text::Update(float dt)
	{

	}

	void Text::Render()
	{

	}

	void Text::CleanUp()
	{

	}
}