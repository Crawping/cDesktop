#pragma once

#include "Icon.h"
#include "Position.h"

class Object : public Icon
{
public:
	class TYPES
	{
	public:
		enum Type
		{
			PLAYER = 0,
			NPC,
			BOX,
			SPIKES,
			POISONING_CLOUD,
			EXIT,

			HEALTH // represents current player health
		};
	};

	Object(std::string name, Position pos, int type);
    Object(std::string name);
	virtual ~Object();

	virtual void onCollision(Object*, Position) {}
	virtual int getType() = 0;
//private:
	// Position position; // already owned by icon so no need to redefine
};

