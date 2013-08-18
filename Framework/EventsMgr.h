#pragma once

#include <vector>
#include <functional>
#include <list>

#include "Event.h"

class EventData
{
	private:
		typedef std::function<void(const Event&, EventData*)> functor;
		EventData(unsigned _eventType, functor _executor) : eventType(_eventType), executor(_executor)
		{}

		std::list<EventData>::iterator ptr;
		unsigned eventType;
		functor executor;

		friend class EventsMgr; // Only EventManager needs using this...
};


class EventsMgr
{
private:
	typedef std::function<void(const Event&, EventData*)> functor;
	friend class Event; // Event can access to propagateEvent()

	std::vector<std::list<EventData>*> funcs; // List of events

public:
	~EventsMgr();

	template<class Class, class EVENT_TYPE>
	EventData* registerEvent(void(Class::*functionPointer)(const EVENT_TYPE&, EventData*), Class* object, unsigned eventType = EVENT_TYPE::getType())
	{
		return registerEvent<EVENT_TYPE>(eventType, std::bind(functionPointer, object, std::placeholders::_1, std::placeholders::_2));
	}
	template<class EVENT_TYPE>
	EventData* registerEvent(void(*functionPointer)(const EVENT_TYPE&, EventData*), unsigned eventType = EVENT_TYPE::getType())
	{
		return registerEvent<EVENT_TYPE>(eventType, std::bind(functionPointer, std::placeholders::_1, std::placeholders::_2));
	}

	void removeEvent(EventData* ed);
	void propagateEvent(const Event &e);

private:
	template <typename EVENT_TYPE>
	EventData* registerEvent(unsigned eventType, std::function<void(const EVENT_TYPE&, EventData*)> funcPtr);
	EventData* registerEvent(unsigned eventType, functor funcPtr);
};


template <typename EVENT_TYPE>
EventData* EventsMgr::registerEvent(unsigned eventType, std::function<void(const EVENT_TYPE&, EventData*)> funcPtr)
{
	// Cast from std::function<void(EVENT_TYPE&, EventData*)>
	// to		 std::function<void(   Event&  , EventData*)>
	// by casting to void* then to target (used in inappriopriate way may be dangerous)
	functor fptr = *((functor*)((void*)(&funcPtr)));
	return registerEvent(eventType, fptr);
}
