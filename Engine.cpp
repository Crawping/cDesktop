#include "stdafx.h"
#include "Engine.h"
#include "winapi.h"

#include "Object.h"
#include "Box.h"
#include "Player.h"
#include "NPC.h"
#include "PoisoningCloud.h"
#include "Spikes.h"
#include "Health.h"
#include "Exit.h"

#include "Events.h"

Engine* Engine::engine = nullptr;

Engine::Engine(void)
    :
    state(STATES::INIT),
    player(nullptr)
{
    engine = this;
    srand(time(0));

    /*
    std::vector<std::string> files = winapi::getFiles(winapi::desktop_path);
    for(std::string file : files)
    {
        //std::cout << "file: " << file << "\n";
        new Box(file);
    }
    */

    int base = winapi::getIcons();

    player = new Player("Steve", Position(5, 5));
    new NPC("NPC1", Position(3, 8));
    new NPC("NPC2", Position(6, 5));
    new NPC("NPC3", Position(11, 5));
    new Health("Health", Position(1, 1)); // 5

    new PoisoningCloud("Trujaca", Position(7, 5));
    new PoisoningCloud("Chmura" , Position(8, 5));
    new Spikes("Kolce", Position(2, 2));

    new Box("Box1", Position(3, 4));
    new Box("Box2", Position(3, 5)); // 10
    new Box("Box3", Position(8, 2));
    new Box("Box4", Position(4, 5));

    new Exit("Wyjscie", Position(8, 8));

    std::cout << "Loading indexes...\n";
    winapi::loadIndexes();
    std::cout << "base: " << base << " curr:" << winapi::indexes.size() << " diff: " << winapi::indexes.size()-base << "\n";
    while(((int)winapi::indexes.size()-base) < 8)
    {
        winapi::loadIndexes();
        std::cout << "base: " << base << " curr:" << winapi::indexes.size() << " diff: " << winapi::indexes.size()-base << "\n";
        Sleep(1000);
    }

    std::cout << "Loading objects...\n";
    for(Object *object : objects)
    {
        object->init();
        winapi::indexes.erase(object->name);
    }

    std::cout << "adding rest of icons...\n";
    for(auto pair : winapi::indexes)
        new Box(pair.first);

    std::cout << "Reloading indexes...";
    winapi::loadIndexes();

    std::cout << "done!\n";
    //TaskData* registerTask(functor funcPointer, float interval);
    //auto renderFunc = std::bind(&Engine::render, this);
    //TM.registerTask(renderFunc, 0.25f);
}


Engine::~Engine(void)
{
    for(Object *o : objects)
        delete o;
}


void Engine::step(float frameTime)
{
	handleEvents();
	TM.step(frameTime);

	//std::cout << "step " << frameTime << "\n";
}


void Engine::handleEvents()
{
    const int W = 0x57;
    const int A = 0x41;
    const int S = 0x53;
    const int D = 0x44;
    if(GetAsyncKeyState(W))
        KeyPressEvent(KeyPressEvent::key::UP).propagate(&EM);
    if(GetAsyncKeyState(S))
        KeyPressEvent(KeyPressEvent::key::DOWN).propagate(&EM);
    if(GetAsyncKeyState(A))
        KeyPressEvent(KeyPressEvent::key::LEFT).propagate(&EM);
    if(GetAsyncKeyState(D))
        KeyPressEvent(KeyPressEvent::key::RIGHT).propagate(&EM);
}


bool Engine::checkCollision(Object *object, Position oldPosition)
{
    Position pos1 = object->getPosition();
    Position pos2;
    bool ret = false;

    for(Object *o : objects)
    {
        if(o == object)
            continue;

        pos2 = o->getPosition();

        /*
        if(pos1.getPosX() == pos2.getPosX()
        && pos1.getPosY() == pos2.getPosY())
        */
        if(pos1 == pos2)
        {
            object->onCollision(o, oldPosition);
            o->onCollision(object, oldPosition);
            ret = true;
        }
    }
    return ret;
}


bool Engine::canPlace(Icon *o, Position where)
{
    for(auto object : engine->objects)
        if(object != o)
            if(object->getPosition() == where)
                return false;
    return true;
}


int Engine::getRandom()
{
    return rand();
}


/*
void Engine::render()
{
    return;

    const int LINES = 20;
    const int COLS = 50;

    static char mapa[LINES][COLS];

    // clear map
    for(int y = 0; y < LINES ; ++y)
        for(int x = 0; x < COLS; ++x)
            mapa[y][x] = '.';

    // fill map
    for(Object *o : objects)
    {
        Position pos = o->getPosition();
        Object::TYPES::Type type = (Object::TYPES::Type)o->getType();
        char ch;

        typedef Object::TYPES::Type obj;
        switch(type)
        {
            case obj::BOX: ch = '#'; break;
            case obj::PLAYER: ch = (char)1; break;
            case obj::NPC: ch = 'O'; break;
            case obj::POISONING_CLOUD: ch = '@'; break;
            case obj::SPIKES: ch = '*'; break;
            case obj::HEALTH: ch = (char)3; break;
            default: ch = '?'; break;
        }
        mapa[pos.getPosY()][pos.getPosX()] = ch;
    }

    std::cout << "\n\n\nHealth: " << (player == nullptr ? 0 : player->getHealth()) << "\n";
    static std::string lines[LINES];
    for(int y = 0; y < LINES; ++y)
    {
        lines[y].clear();
        for(int x = 0; x < COLS; ++x)
            lines[y] += mapa[y][x];
        lines[y] += "\n";
    }

    std::string screen;
    for(int i = 0; i < LINES; ++i)
        screen += lines[i];
        //std::cout << lines[i];
    std::cout << screen;
}
*/
