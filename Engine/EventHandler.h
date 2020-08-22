#ifndef _EVENT_HANDLER_H_
#define _EVENT_HANDLER_H_

namespace GameEngine {

	// Abstract Class for EventHandler to notify of a change
	class EventHandlerBase {
		public:
			virtual void Execute() = 0;
	};

	// Event Handler Class : Handles Callback
	template<typename T>
	class EventHandler : public EventHandlerBase {
		// Defining type for function pointer

		public:
			// Object of the Listener
			T* object;
			// Function for callback
			void (T::* function)(void);

			EventHandler() {};

			EventHandler(T* obj, void (T::* func)(void)) {
				object = obj;
				function = func;
			}
			void Execute() {
				(object->*function)();
			}
	};
}

#endif