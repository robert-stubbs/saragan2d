
#ifndef _C_GCDISPATCH_H_
#define _C_GCDISPATCH_H_

#include <deque>
namespace GameEngine
{
	enum MESSAGELEVEL {
		ALL = 0,
		ENTITY,
		ENTITY_COMPONENT,
		ENTITY_CHILDREN,
		ENTITY_LISTENERS,
		PLAYERS,
		WORLD,
		TERMINATE
	};

	enum MESSAGETYPE
	{
		HITTEST = 0,
		HOVERTEST,
		IAMDEAD,
		DESTROY,
		CREATE,
		DAMAGE,
		DIDENTER,
		DIDEXIT,
		DIDTOUCH,
		COLLIDE
	};

	struct SystemMessage
	{
		int MessageID;
		std::string MessageName;
		MESSAGETYPE MessageType;
		MESSAGELEVEL MessageLevel;
		std::string entity_handle;
		std::string target;
		std::map<std::string, std::string> stringValues;
		std::map<std::string, float> floatValues;

	};

	class GCDispatch
	{
	public:
		// TODO - ADD functionality to set Listeners
		/*
			Listener
					entityID  listeners
				map<string, <vector<string>>

			here we can say for this entity if it sends a message then deliver to these entities only? only of certain message level though
			say
				Level 0 - All entities
				Level 1 - Entities that Can recieve that type of message
				Level 2 - Listeners Only?
				Level 3 - Entity Component

		*/
		int MessageIDPool;

		GCDispatch();
		~GCDispatch();

		int getNextID();

		bool dispatch(SystemMessage msg);
		void RunMessage(SystemMessage msg);
		void addMessage(std::string MessageName, std::string sourceHandle, std::string target, std::map<std::string, std::string> stringVals);
		void addMessage(std::string MessageName, std::string sourceHandle, std::string target, std::map<std::string, float> floatVals);

		void addListener(std::string entity, std::string Listener);
		void removeListener(std::string entity, std::string Listener);

		SystemMessage getNextMessage(std::string Name, MESSAGETYPE type, MESSAGELEVEL level, std::string eHandle, std::string target);

	private:
		std::deque<SystemMessage> m_messages;
		std::map <std::string, std::vector<std::string>> m_listeners;
	};
}



#endif