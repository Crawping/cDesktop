#include "stdafx.h"
#include "Position.h"

#include "Icon.h"

Position::Position(float posX, float posY)
    :
    posX(posX),
    posY(posY)
{
}


Position::~Position(void)
{
}

void Position::setPosition(float posX, float posY)
{
	this->posX = posX;
	this->posY = posY;
}


float Position::getPosX()
{
	return posX;
}


float Position::getPosY()
{
	return posY;
}


bool Position::operator==(Position& pos)
{
    return(this->posX >= pos.getPosX() - Icon::width  / 2
        && this->posY >= pos.getPosY() - Icon::height / 2
        && this->posX <= pos.getPosX() + Icon::width  / 2
        && this->posY <= pos.getPosY() + Icon::height / 2);
    /*
    return (this->posX == pos.getPosX()
         && this->posY == pos.getPosY());
    */
}
