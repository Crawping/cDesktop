#pragma once

#include <vector>
#include <string>

#include "Framework/EventsMgr.h"
#include "Framework/TasksMgr.h"

#include "Position.h"

class Icon;
class Object;
class Player;

class Engine
{
public:
	class STATES
	{
	public:
		enum State
		{
			INIT = 0,
			GAME,
			EXIT
		};
	};

	int state;
	float frameTime;

	EventsMgr EM;
	TasksMgr  TM;

	Engine(void);
	~Engine(void);

	void step(float frameTime);
	void handleEvents();
	void render();

	bool checkCollision(Object *object, Position oldPosition);

	Player *player;
	std::vector<Object*> objects;
	void addObject(Object *object) { objects.push_back(object); }
	bool canPlace(Icon *o, Position where);

	int getRandom();

	static Engine *engine;
	static Engine* get() { return engine; }
};

