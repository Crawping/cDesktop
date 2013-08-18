#pragma once
#include <vector>
#include <list>
#include <functional>

class TaskTimer
{
public:
	TaskTimer(float _interval, float _time) : interval(_interval), time(_time)
	{}

	float interval; // how much time to wait before run the task
	float time; // how much time passed
};

class TaskData
{
private:
	typedef std::function<void(TaskData*)> functor;
	typedef std::list<TaskData>* funcs;
	TaskData(float _interval, functor _executor) : interval(_interval), executor(_executor)
	{}

	funcs listPtr;
	std::list<TaskData>::iterator ptr;
	float interval;
	functor executor;

	friend class TasksMgr; // Only Tasks needs using this...
};

class TasksMgr
{
private:
	typedef std::function<void(TaskData*)> functor;
	typedef std::list<TaskData>* funcs;
	typedef std::vector<std::pair<TaskTimer*, funcs>>::iterator iterator;
	typedef std::list<TaskData>::iterator tasksIterator;

public:
	~TasksMgr();

	// time - time passed since last step
	void step(float time);

	template<class Class>
	TaskData* registerTask(void(Class::*functionPointer)(TaskData*), Class* object, float interval)
	{
		return registerTask(std::bind(functionPointer, object, std::placeholders::_1), interval);
	}
	TaskData* registerTask(void(*functionPointer)(TaskData*), float interval)
	{
		return registerTask(std::bind(functionPointer, std::placeholders::_1), interval);
	}
	TaskData* registerTask(functor funcPointer, float interval);

	void removeTask(TaskData *td);

private:
	std::vector<std::pair<TaskTimer*, std::list<TaskData>*>> tasks;
};