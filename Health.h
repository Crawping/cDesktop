#ifndef HEALTH_H
#define HEALTH_H

#include "Object.h"

#include "Events.h"

class EventData;

class Health : public Object
{
public:
	Health(std::string name, Position pos);
	~Health(void);

	void onPlayerHurt(const PlayerHurtEvent &, EventData *); // changes its name to player health

	void setHealth(int health);

	int getType() { return Object::TYPES::HEALTH; }
};

#endif // HEALTH_H
