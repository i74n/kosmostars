#pragma once
#include "Entity.h"

class Asteroid:public Entity{
	int reward;
	Texture explosionTexture;
	Sprite explosionSprite;
	float explosionFrame;
	float scale;
	Vector2f speed;
	Status status;
public:
	int hp;
	Asteroid();
	Asteroid(float x, float y, float speedX, float speedY);
	Status update(float time);
	void setScale();
	float getScale();
	void getDamage();
	bool isAlive();
	int getReward();
	Sprite explosion(float time);
};