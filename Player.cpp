#include "stdafx.h"
#include "Player.h"
#include "Engine.h"
#include "winapi.h"
#include "Events.h"

Player::Player(std::string name, Position position)
    :
    Object(name, position, Object::TYPES::Type::PLAYER),
    health(100),
    locked(false)
{
    Engine *engine = Engine::get();
    engine->player = this;

    EventsMgr& EM = engine->EM;

    keyPressEvent = EM.registerEvent(&Player::onKeyboardKeyPress, this);
    moveEvent     = EM.registerEvent(&Player::onPlayerMove      , this);
    hurtEvent     = EM.registerEvent(&Player::onPlayerHurt      , this);
}


Player::~Player(void)
{
}


void Player::onKeyboardKeyPress(const KeyPressEvent &event, EventData *)
{
    //if(locked)
    //    return;
    //lock();
    //TasksMgr& TM = Engine::get()->TM;
    //TM.registerTask(&Player::unlock, this, 0.0025); // Lock next keypresses for 0.0025s

    Position position = getPosition();
    Position oldPosition = position;

    float ft = Engine::get()->frameTime;
    KeyPressEvent::key key = event.keyPressed;
    switch(key)
    {
    case KeyPressEvent::key::UP:
        position.setPosition(position.getPosX(), position.getPosY()-1*ft);
        break;
    case KeyPressEvent::key::DOWN:
        position.setPosition(position.getPosX(), position.getPosY()+1*ft);
        break;
    case KeyPressEvent::key::RIGHT:
        position.setPosition(position.getPosX()+1*ft, position.getPosY());
        break;
    case KeyPressEvent::key::LEFT:
        position.setPosition(position.getPosX()-1*ft, position.getPosY());
        break;
    default:
        return;
    };

    setPos(position);
    Engine::get()->checkCollision(this, oldPosition);

    /**
    this->position.setPosition(position.getPosX(), position.getPosY()); // update position to check collision below. Don't move it on the desktop yet
    if(!Engine::get()->checkCollision(this, oldPosition))
        setPos(position);
    */
}


void Player::onPlayerMove(const PlayerMoveEvent &, EventData *)
{
}


void Player::onPlayerHurt(const PlayerHurtEvent &event, EventData *)
{
    Player *p = event.player;
    if(this != p)
        return;

    health -= event.damage;
    std::cout << "health: " << health << "\n";
}


void Player::lock()
{
    locked = true;
}


void Player::unlock(TaskData *TD)
{
    locked = false;
    TasksMgr& TM = Engine::get()->TM;
    TM.removeTask(TD);
}
