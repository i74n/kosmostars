#pragma once
#include "Entity.h"
#include "Bonus.h"

class Player:public Entity{
	int scores;
	float shot_cooldown;
public:
	Player();
	Status update(float time);
	void setBuff(Buff buff);
	std::string getScores();
	void setScores(int crement);
};