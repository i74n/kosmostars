#pragma once
#include "Entity.h"

class Bonus:public Entity{
public:
	Buff buff;
	Bonus(Image & image, Vector2f playerPose);
	Status update(float time);
	bool isAlive();
	Buff getBuff();
};