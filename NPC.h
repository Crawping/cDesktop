#pragma once

#include "Object.h"

#include "Events.h"

class TaskData;

class NPC : public Object
{
public:
    int moves, randX, randY, newX, newY;

	NPC(std::string name, Position pos);
	~NPC(void);

	int getType() { return Object::TYPES::Type::NPC; }

	void move(TaskData*);
};
