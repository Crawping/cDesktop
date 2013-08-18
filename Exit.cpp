#include "stdafx.h"
#include "Exit.h"

#include "Engine.h"

Exit::Exit(std::string name, Position position)
    :
    Object(name, position, Object::TYPES::Type::EXIT)
{
}


Exit::~Exit()
{

}


void Exit::onCollision(Object *object, Position)
{
    if(object->getType() != Object::TYPES::Type::PLAYER)
        return;

    Engine::get()->state = Engine::STATES::State::EXIT;
}
