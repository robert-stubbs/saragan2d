#include "EnginePCH.h"
#include "Event.h"

namespace GameEngine
{
	template <typename T>
	void Event::AddListener(T* obj, void (T::* func)(void)) {
		handlers.push_back(new EventHandler<T>(obj, func));
	}

	void Event::Execute() {
		for (EventHandlerBase* e : handlers) {
			e->Execute();
		}
	}

}