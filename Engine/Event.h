#ifndef _EVENT_H_
#define _EVENT_H_

#include "EventHandler.h"

namespace GameEngine {

	class Event {

		private:
			std::vector<EventHandlerBase*> handlers = std::vector<EventHandlerBase*>();
			
		public:

			template <typename T>
			void AddListener(T* obj, void (T::* func)(void));

			void Execute();

	};

}

#endif