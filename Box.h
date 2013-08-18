#pragma once
#include "Object.h"

#include "Events.h"

class EventData;

class Box : public Object
{
public:
	Box(std::string name, Position pos);
    Box(std::string name);
	~Box();

	void onCollision(Object *object, Position oldPosition);

	int getType() { return Object::TYPES::BOX; }

	bool moveBox(Position);
};
