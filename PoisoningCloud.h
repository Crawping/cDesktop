#pragma once
#include "Object.h"

#include "Events.h"

class EventData;
class TaskData;

class PoisoningCloud : public Object
{
public:
	PoisoningCloud(std::string name, Position pos);
	~PoisoningCloud(void);

	void onCollision(Object *object, Position oldPosition);
	void onPlayerPoisoned(const PlayerPoisonedEvent&, EventData*); // calls PlayerHurt every 2 seconds

	void hurtPlayer(TaskData*);
	void cancelHurt(TaskData*);

	int getType() { return Object::TYPES::POISONING_CLOUD; }

private:
    Player *poisonedPlayer;
    TaskData *hurtTask, *cancelTask;
};

