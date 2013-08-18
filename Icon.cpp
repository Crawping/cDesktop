#include "stdafx.h"
#include "Icon.h"

#include "winapi.h"
#include "Engine.h"
#include "Object.h"

Icon::Icon(std::string name, std::string path, Position pos, int type)
    :
    name(name+".ico"),
    path(path),
    position(pos),
    isOwnIcon(true)
{
    winapi::createFile(name, type);
}


Icon::Icon(std::string name)
    :
    name(name),
    isOwnIcon(false)
{
    //index = winapi::getIndex(name);
    position = winapi::getPosition(getIndex());
    std::cout << "loaded " << name << " " << getIndex() << " at " << position.getPosX() << " " << position.getPosY() << "\n";
}


int Icon::getIndex()
{
    return winapi::getIndexOf(name);
}


void Icon::init()
{
    //index = winapi::getIndex(name);
    if(!isOwnIcon)
        position = winapi::getPosition(getIndex());
    setPos(position);
}


Icon::~Icon()
{
    if(isOwnIcon)
        winapi::deleteFile(name);
}


void Icon::setName(std::string name)
{
    winapi::rename(this->name, name);
    this->name = name;
}


void Icon::setPos(Position pos)
{
    winapi::setPosition(getIndex(), pos.getPosX(), pos.getPosY());
    position.setPosition(pos.getPosX(), pos.getPosY());
}

bool Icon::canPlace(Position pos)
{
    Engine *engine = Engine::get();
    return engine->canPlace(this, pos);
}
