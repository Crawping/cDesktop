#include "stdafx.h"
#include "Object.h"

#include "Engine.h"
#include "winapi.h"

Object::Object(std::string name, Position position, int type)
    :
    Icon(name, winapi::desktop_path, Position(position.getPosX()*Icon::width, position.getPosY()*Icon::height), type)
{
    Engine::get()->addObject(this);
}


Object::Object(std::string name)
    :
    Icon(name)
{
    Engine::get()->addObject(this);
}


Object::~Object(void)
{
}
