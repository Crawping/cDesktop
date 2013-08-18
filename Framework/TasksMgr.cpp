#include "../stdafx.h"
#include "TasksMgr.h"


TasksMgr::~TasksMgr()
{
	for(auto it : tasks)
	{
		delete it.first;  // TaskTimer*
		delete it.second; // List<TaskData>*
	}
}


void TasksMgr::step(float time)
{
	// get through all registered tasks
	// Don't make this for loop "for(auto it : tasks)"
	// because the vector we are looping over may reallocate causing iterator to invalidate. So just use this "old" but WORKING way ;)
	for(unsigned i = 0; i < tasks.size(); ++i)
	{
		auto it = tasks[i];

		if (time >= it.first->time) // has time passed limit?
		{
			it.first->time = it.first->interval; // reset counter
			// get through all registered functions for this task
			for(auto it2 = it.second->begin(), next = it2; it2 != it.second->end(); it2 = next)
			{
				next++;
				(it2->executor)(&*it2); // calls a function stored in it2
			}
		}
		else
			it.first->time -= time;
	}
}


TaskData* TasksMgr::registerTask(functor funcPointer, float interval)
{
	TaskData data(interval, funcPointer);

	// search a good place to put this task
	for (auto it = tasks.begin(); it != tasks.end(); ++it)
	{
		if (it->first->interval == interval)
		{
			funcs list = it->second;
			data.listPtr = list;
			list->push_back(data);
			list->rbegin()->ptr = --list->rbegin().base();
			return &*list->rbegin();
		}
	}

	// if good place not found, add new place
	funcs v = new std::list<TaskData>();
	v->push_back(data);
	tasks.push_back(std::make_pair(new TaskTimer(interval, 0.f), v));

	auto datait = tasks.rbegin()->second->begin();
	datait->listPtr = tasks.rbegin()->second;
	datait->ptr = datait;
	return &*datait;
}


void TasksMgr::removeTask(TaskData *td)
{
	td->listPtr->erase(td->ptr);
}
