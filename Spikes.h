#pragma once
#include "Object.h"

class TaskData;

class Spikes : public Object
{
public:
	Spikes(std::string name, Position pos);
	~Spikes(void);

	void onCollision(Object *object, Position oldPosition);
	void lock();
	void unlock(TaskData *TD);

	int getType() { return Object::TYPES::SPIKES; }

private:
    bool locked;
};

