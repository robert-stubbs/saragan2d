#include "EnginePCH.h"
#include "EventManager.h"

namespace GameEngine
{
	EventManager EventManager::_Instance = EventManager();

	void EventManager::CreateNewEvent(std::string name) {

		for (EventType e : _events)
		{
			if (e.name.compare(name) == 0)
			{
				return;
			}
		}

		_events.push_back({ new Event(), name });
	}

	template <typename T>
	bool EventManager::Subscribe(std::string name, T* obj, void (T::* func)(void))
	{
		for (EventType e : _events)
		{
			if (e.name.compare(name) == 0)
			{
				e.event->addListener(obj, func);
				return true;
			}
		}

		return false;
	}

	void EventManager::Execute(std::string name) {

		for (EventType e : _events)
		{
			if (e.name.compare(name) == 0)
			{
				e.event->Execute();				
			}
		}
	}
}