#include "EnginePCH.h"
#include "LabelEntity.h"

#include "Engine.h"
#include "SystemManager.h"
#include "Text.h"

#include "Dispatch.h"


LabelEntity::LabelEntity()
{

}

LabelEntity::~LabelEntity()
{

}

void LabelEntity::InitWithPositionAndText(float x, float y, std::string text)
{
	//cGUISystem* sgui = (cGUISystem*)(Engine::getEngine().System->getSystem("GUI"));

	//if (sgui != nullptr) {
	//	cText* textItem = new cText();
	//	textItem->Init();
	//	textItem->ent = this;
	//	textItem->m_handle = m_handle;

	//	textItem->SetString(&sgui->Fonts["Main20"], text, x, y, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//	sgui->AddComponentObject(textItem);
	//}
}

void LabelEntity::UpdateLabel(std::string text)
{
	if (m_components.size() == 1) {
		Text* textItem = (Text*)m_components.at(0).get();
		textItem->changeText(text);
	}
}

bool LabelEntity::handleMessage(SystemMessage msg)
{
	if (msg.MessageLevel == ENTITY_COMPONENT)
	{
		for (iter = m_components.begin(); iter != m_components.end(); iter++)
		{
			(*iter)->handleMessage(msg);
		}
		return true;
	}

	//switch (msg.MessageType)
	//{
	//	default:
	//	{
	//	}break;

	//}

	return false;
}