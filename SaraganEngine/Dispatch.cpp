#include "EnginePCH.h"
#include "EngineLibrary.h"
#include "Dispatch.h"

#include "cErrorLogger.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Engine.h"

GCDispatch::GCDispatch()
{
	MessageIDPool = 0;
}


GCDispatch::~GCDispatch()
{
}

int GCDispatch::getNextID()
{
	int next = MessageIDPool;
	MessageIDPool++;
	return next;
}

void GCDispatch::RunMessage(SystemMessage msg)
{
	//boost::thread(&GCDispatch::dispatch, this, msg);
}

bool GCDispatch::dispatch(SystemMessage msg)
{
	cErrorLogger::Log().WriteToConsole("> MessageName: ");
	cErrorLogger::Log().WriteToConsole(msg.MessageName);
	cErrorLogger::Log().WriteToConsole(" entity_handle: ");
	cErrorLogger::Log().WriteToConsole(msg.entity_handle);
	cErrorLogger::Log().WriteToConsole(" target: ");
	cErrorLogger::Log().WriteToConsole(msg.target);
	cErrorLogger::Log().WriteToConsole("\n");

	switch (msg.MessageLevel)
	{
	case ALL:	// send to ALL entities
	{
		std::map< std::string, SharedEntityPtr >::iterator End = Engine::getEngine().EntityMgr->m_entities.end();
		std::map< std::string, SharedEntityPtr >::iterator it = Engine::getEngine().EntityMgr->m_entities.begin();

		for (it; it != End; ++it)
		{
			bool response = (it->second.get())->handleMessage(msg);
			if (response)
			{
				return true;
			}
		}
		return false;

	} break;

	case ENTITY: // send to selected Entity
	{
		Entity* ent = Engine::getEngine().EntityMgr->getEntity(msg.target);
		if (ent != nullptr)
		{
			return ent->handleMessage(msg);
		}
	} break;

	case ENTITY_COMPONENT: // send to Entity but components
	{
		Entity* ent = Engine::getEngine().EntityMgr->getEntity(msg.target);
		return ent->handleMessage(msg);
	} break;

	case ENTITY_CHILDREN: // send to Entity but components
	{
		Entity* ent = Engine::getEngine().EntityMgr->getEntity(msg.target);
		return ent->handleMessage(msg);
	} break;

	case ENTITY_LISTENERS: // send to listeners ? should this be in all cases anyway?
	{
		std::vector<std::string>listenerList = m_listeners[msg.entity_handle];
		for (std::vector<std::string>::iterator it = listenerList.begin(); it != listenerList.end(); it++)
		{
			Entity* ent = Engine::getEngine().EntityMgr->getEntity(*it);
			bool response = ent->handleMessage(msg);
			if (response)
			{
				return true;
			}
		}
		return false;
	} break;

	//case PLAYERS: // Players Only
	//{
	//	if (pWorld->currentPlayer != nullptr)
	//	{
	//		return pWorld->currentPlaycErrorLogger::Log().handleMessage(msg);
	//	}
	//}break;

	//case WORLD:
	//{
	//	pWorld->isLoaded = true;
	//	return true;
	//} break;

	case TERMINATE:
	{
		SendMessage(hWnd, WM_CLOSE, NULL, NULL);
	}break;
	}
	return false;
}

void GCDispatch::addMessage(std::string MessageName, std::string sourceHandle, std::string target, std::map<std::string, std::string> stringVals)
{
	SystemMessage msg;
	msg.MessageID = 0;
	msg.MessageName = MessageName;
	msg.entity_handle = sourceHandle;
	msg.target = target;
	msg.stringValues = stringVals;
	m_messages.push_back(msg);
}

void GCDispatch::addMessage(std::string MessageName, std::string sourceHandle, std::string target, std::map<std::string, float> floatVals)
{
	SystemMessage msg;
	msg.MessageID = 0;
	msg.MessageName = MessageName;
	msg.entity_handle = sourceHandle;
	msg.target = target;
	msg.floatValues = floatVals;
	m_messages.push_back(msg);

}



void GCDispatch::addListener(std::string entity, std::string Listener)
{
	std::vector<std::string> listeners = m_listeners[entity];
	listeners.push_back(Listener);
	m_listeners[entity] = listeners;

}
void GCDispatch::removeListener(std::string entity, std::string Listener)
{
	std::vector<std::string> listeners = m_listeners[entity];
	if (!listeners.empty())
	{
		for (std::vector<std::string>::iterator it = listeners.begin(); it != listeners.end(); it++)
		{
			if (*it == Listener)
			{
				listeners.erase(it);
				break;
			}
		}
		m_listeners[entity] = listeners;
	}
}


SystemMessage GCDispatch::getNextMessage(std::string Name, MESSAGETYPE type, MESSAGELEVEL level, std::string eHandle, std::string target)
{
	SystemMessage foo;
	foo.MessageID = getNextID();
	foo.MessageName = Name;
	foo.MessageType = type;
	foo.MessageLevel = level;
	foo.entity_handle = eHandle;
	foo.target = target;

	return foo;
}
