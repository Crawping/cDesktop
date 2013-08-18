#pragma once
class Position
{
public:
	Position(float posX = 0, float posY = 0);
	~Position(void);

	void setPosition(float posX, float posY);
	float getPosX();
	float getPosY();

	bool operator==(Position& position);

private:
	float posX, posY;
};

