#include "stdafx.h"
#include "Engine.h"
#include "cTimer.h"

int main()
{
	Engine engine;
	engine.state = Engine::STATES::GAME;

	float frametime = 0.f;

	cTimer timer;

	while(engine.state != Engine::STATES::EXIT)
	{
	    frametime = timer.getTimeStamp();
	    engine.frameTime = frametime * 250;
	    engine.step(frametime);
	}
	std::cout << "Wylaczanie gry\n";
}
