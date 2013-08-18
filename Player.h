#pragma once

#include "Object.h"

#include "Events.h"

class EventData;
class TaskData;

class Player : public Object
{
public:
	Player(std::string name, Position pos);
	~Player(void);

	void onKeyboardKeyPress(const KeyPressEvent&, EventData*); // calls MoveEvent
	void onPlayerMove(const PlayerMoveEvent&, EventData*); // calls PlayerHurt, ApplyPoison
	void onPlayerHurt(const PlayerHurtEvent&, EventData*); // calls PlayerDie

	int getType() { return Object::TYPES::PLAYER; }
	int getHealth() { return health; }

	void lock();
	void unlock(TaskData *);

	EventData *keyPressEvent;
	EventData *moveEvent;
	EventData *hurtEvent;
	EventData *poisonedEvent;
private:
	int health; // 0-100
	bool locked;
};
