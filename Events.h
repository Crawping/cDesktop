#pragma once

#include "Framework/Event.h"
#include "EventTypes.h"

class Object;
class Box;
class Player;
class PoisoningCloud;
class Spikes;
class Health;

class KeyPressEvent : public Event
{
public:
    enum key
	{
	    UP=0,
	    DOWN,
	    RIGHT,
	    LEFT
	};

	KeyPressEvent(key keyPressed)
        : Event(EventTypes::KEY_PRESS), keyPressed(keyPressed)
	{}

	key keyPressed;

	static unsigned getType() { return EventTypes::EventType::KEY_PRESS; }
};


class PlayerMoveEvent : public Event
{
public:
	PlayerMoveEvent(Player *p)
        : Event(EventTypes::PLAYER_MOVE), player(p)
	{}
	Player *player;

	static unsigned getType() { return EventTypes::EventType::PLAYER_MOVE; }
};


class PlayerHurtEvent : public Event
{
public:
	PlayerHurtEvent(Player *p, int damage)
        : Event(EventTypes::PLAYER_HURT), player(p), damage(damage)
	{}
	Player *player;
	int damage;

	static unsigned getType() { return EventTypes::EventType::PLAYER_HURT; }
};


class PlayerPoisonedEvent : public Event
{
public:
	PlayerPoisonedEvent(Player *p, PoisoningCloud *cloud, float time)
        : Event(EventTypes::PLAYER_POISONED), player(p), poisoningCloud(cloud), time(time), timePassed(0)
	{}
	Player *player;
	PoisoningCloud *poisoningCloud;
	float time;
	float timePassed;

	static unsigned getType() { return EventTypes::EventType::PLAYER_POISONED; }
};


class BoxMoveEvent : public Event
{
public:
	BoxMoveEvent(Box *box, Position newPosition)
        : Event(EventTypes::BOX_MOVE), box(box), newPosition(newPosition)
	{}
	Box *box;
	Position newPosition;

	static unsigned getType() { return EventTypes::EventType::BOX_MOVE; }
};

