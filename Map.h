#pragma once
#include "Entity.h"

class Map:public Entity{
	float displace;
public:
	Map(Image & image);
	Status update(float time);
	bool isAlive();
};