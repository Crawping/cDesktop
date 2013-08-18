#include "NPC.h"

#include "Engine.h"

#include "Events.h"

NPC::NPC(std::string name, Position position)
    :
    Object(name, position, Object::TYPES::Type::NPC)
{
    TasksMgr &TM = Engine::get()->TM;
    TM.registerTask(&NPC::move, this, 0.01f);

    moves = randX = randY = newX = newY = 0;
}


NPC::~NPC(void)
{
}


void NPC::move(TaskData*)
{
    if(moves > 0)
    {
        Position pos = getPosition();
        newX = pos.getPosX() + randX;
        newY = pos.getPosY() + randY;
        if(newX < 0) newX = 0;
        if(newX > 800) newX = 800;
        if(newY < 0) newY = 0;
        if(newY > 600) newY = 600;

        pos.setPosition(newX, newY);
        if(canPlace(pos))
            setPos(pos);

        moves--;
    }
    else
    {
        randX = Engine::get()->getRandom() % 3 - 1;
        randY = Engine::get()->getRandom() % 3 - 1;
        moves = rand() % 75;
    }
}
