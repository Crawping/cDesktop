#pragma once
#include "Object.h"

class Exit : public Object
{
public:
	Exit(std::string name, Position pos);
	~Exit();

	void onCollision(Object *object, Position oldPosition);

	int getType() { return Object::TYPES::EXIT; }
};
