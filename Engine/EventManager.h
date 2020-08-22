#ifndef _EVENT_MANAGER_H_
#define _EVENT_MANAGER_H_

#include "Types.h"
#include "Event.h"
#include "EventHandler.h"

namespace GameEngine {

	class EventManager {
		private:
			std::vector<EventType> _events;

			static EventManager _Instance;

			EventManager() {};
		public:

			static EventManager& Instance() {
				return _Instance;
			}

			void CreateNewEvent(std::string name);

			template <typename T>
			bool Subscribe(std::string name, T* obj, void (T::* func)(void));

			void Execute(std::string name);
	};
}

#endif