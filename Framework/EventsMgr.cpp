#include "../stdafx.h"
#include "EventsMgr.h"

EventsMgr::~EventsMgr()
{
	for(auto it : funcs)
		delete it; // std::list<EventData>*
}


void EventsMgr::removeEvent(EventData* ed)
{
	funcs[ed->eventType]->erase(ed->ptr);
}


EventData* EventsMgr::registerEvent(unsigned eventType, functor fptr)
{
	// Fit array size for new events
	while(funcs.size() <= eventType)
		funcs.push_back(new std::list<EventData>());

	EventData ed(eventType, fptr);
	funcs[eventType]->push_back(ed); // Add event to list
	funcs[eventType]->rbegin()->ptr = --funcs[eventType]->rbegin().base();
	return &*funcs[eventType]->rbegin();
}


void EventsMgr::propagateEvent(const Event &e)
{
	// Iterate through all pointers for event and call them
	if(funcs.size() > (unsigned)e.type)
	{
		std::list<EventData>* funcList = funcs[e.type];
		for(auto it = funcList->begin(), next = it; it != funcList->end(); it = next)
		{
			next++;
			it->executor(e, &*it);
		}
	}
}
