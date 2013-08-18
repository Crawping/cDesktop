#include "PoisoningCloud.h"

#include "Engine.h"

#include "Events.h"
#include "Player.h"

PoisoningCloud::PoisoningCloud(std::string name, Position position)
    :
    Object(name, position, Object::TYPES::Type::POISONING_CLOUD),
    hurtTask(nullptr),
    cancelTask(nullptr)
{
    EventsMgr& EM = Engine::get()->EM;
    EM.registerEvent(&PoisoningCloud::onPlayerPoisoned, this);
}


PoisoningCloud::~PoisoningCloud(void)
{
}


void PoisoningCloud::onCollision(Object *object, Position oldPosition)
{
    if(object->getType() != Object::TYPES::Type::PLAYER)
        return;

    EventsMgr& EM = Engine::get()->EM;
    PlayerPoisonedEvent((Player*)object, this, 5.f).propagate(&EM);

    object->setPos(oldPosition);
}


void PoisoningCloud::onPlayerPoisoned(const PlayerPoisonedEvent &event, EventData *)
{
    if(event.poisoningCloud != this)
        return;

    if(this->hurtTask != nullptr)
        cancelHurt(cancelTask);
    poisonedPlayer = event.player;

    TasksMgr& TM = Engine::get()->TM;
    this->hurtTask   = TM.registerTask(&PoisoningCloud::hurtPlayer, this, 0.5f);
    this->cancelTask = TM.registerTask(&PoisoningCloud::cancelHurt, this, event.time);
}


void PoisoningCloud::hurtPlayer(TaskData*)
{
    EventsMgr& EM = Engine::get()->EM;
    PlayerHurtEvent(poisonedPlayer, 1).propagate(&EM);
}


void PoisoningCloud::cancelHurt(TaskData *TD)
{
    TasksMgr& TM = Engine::get()->TM;
    TM.removeTask(this->hurtTask);
    TM.removeTask(TD);

    this->hurtTask   = nullptr;
    this->cancelTask = nullptr;
}
