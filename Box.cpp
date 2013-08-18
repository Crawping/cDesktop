#include "stdafx.h"
#include "Box.h"

#include "Engine.h"
#include "Events.h"

Box::Box(std::string name, Position position)
    :
    Object(name, position, Object::TYPES::Type::BOX)
{
}


Box::Box(std::string name)
    :
    Object(name)
{
}


Box::~Box()
{

}


void Box::onCollision(Object *object, Position oldPosition)
{
    if(object->getType() != Object::TYPES::Type::PLAYER)
        return;

    Position newPosition = object->getPosition();
	int newX = newPosition.getPosX();
    int newY = newPosition.getPosY();
    int oldX = oldPosition.getPosX();
    int oldY = oldPosition.getPosY();

    int changeX = newX - oldX;
    int changeY = newY - oldY;
    float ft = Engine::get()->frameTime;
    changeX *= ft;
    changeY *= ft;

    Position myPosition = getPosition();
    int myX = myPosition.getPosX();
    int myY = myPosition.getPosY();
    newPosition.setPosition(myX + changeX, myY + changeY);

    if(!moveBox(newPosition))
        object->setPos(oldPosition); // return player to previous position
}


bool Box::moveBox(Position newPosition)
{
    Position oldPosition = getPosition();
    if(canPlace(newPosition))
        setPos(newPosition);
    else
        return false;
    return true;
}
