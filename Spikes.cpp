#include "Spikes.h"

#include "Engine.h"

#include "Events.h"

Spikes::Spikes(std::string name, Position position)
    :
    Object(name, position, Object::TYPES::Type::SPIKES)
{
}


Spikes::~Spikes(void)
{
}


void Spikes::onCollision(Object *object, Position oldPosition)
{
    if(object->getType() != Object::TYPES::Type::PLAYER)
        return;

    EventsMgr& EM = Engine::get()->EM;
    if(!locked)
        PlayerHurtEvent((Player*)object, 5).propagate(&EM);
    lock();
    TasksMgr& TM = Engine::get()->TM;
    TM.registerTask(&Spikes::unlock, this, 1.15f); // Lock next hurt for 1.15s

    object->setPos(oldPosition);
}


void Spikes::lock()
{
    locked = true;
}


void Spikes::unlock(TaskData *TD)
{
    locked = false;
    TasksMgr& TM = Engine::get()->TM;
    TM.removeTask(TD);
}
