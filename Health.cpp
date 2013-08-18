#include "stdafx.h"
#include "Health.h"

#include "Engine.h"

#include "Events.h"
#include "Player.h"


Health::Health(std::string name, Position position)
    :
    Object(name, position, Object::TYPES::Type::HEALTH)
{
    EventsMgr& EM = Engine::get()->EM;
    EM.registerEvent(&Health::onPlayerHurt, this);

    setHealth(100);
}


Health::~Health(void)
{
}


#include <iostream>
void Health::onPlayerHurt(const PlayerHurtEvent &event, EventData *)
{
    int health = event.player->getHealth();
    health -= event.damage;

    if(health <= 0)
        Engine::get()->state = Engine::STATES::State::EXIT;
    else
        setHealth(health);
}


void Health::setHealth(int health)
{
    setName(std::to_string(health) + ".ico");
}
