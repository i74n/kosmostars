#pragma once
#include "Entity.h"

class Player:public Entity{
	int scores;
	float shot_cooldown;
	float buffTime;
	Buff buff;
public:
	Player(Image & image);
	Status update(float time);
	void setBuff(Buff buff);
	std::string getScores();
	void setScores(int crement);
	Status getStatus();
	Buff getBuff();
	std::string getBuffTimeLeft();
};