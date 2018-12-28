#include "Asteroid.h"

Asteroid::Asteroid(){
	explosionFrame = 0; 
	setScale();

	hp = 4*scale;
	speed.x = 2/scale;
	speed.y = 0;
	reward = 12*scale;
	
	switch (rand()%2){
	case 0: makeTexture("images/asteroid0.png", scale);break;
	case 1: makeTexture("images/asteroid1.png", scale);break;
	case 2: makeTexture("images/asteroid2.png", scale);break;
	}

	setPosition(900, rand()%(540-size.x));

	explosionTexture.loadFromFile("images/explosion.png");
	explosionSprite.setTexture(explosionTexture);
	explosionSprite.setScale(3*scale, 3*scale); 
}

Asteroid::Asteroid(float x, float y, float speedX, float speedY){
	explosionFrame = 0; 
	scale = 0.25;

	hp = 1;
	speed.x = speedX;
	speed.y = speedY;
	reward = 3;

	switch (rand()%2){
	case 0: makeTexture("images/asteroid0.png", scale);break;
	case 1: makeTexture("images/asteroid1.png", scale);break;
	case 2: makeTexture("images/asteroid2.png", scale);break;
	}

	setPosition(x, y);

	explosionTexture.loadFromFile("images/explosion.png");
	explosionSprite.setTexture(explosionTexture);
	explosionSprite.setScale(0.75, 0.75); 
}

Status Asteroid::update(float time){
	if (status == alive){
		position.x -= speed.x*time*500;
		position.y -= speed.y*time*500;
		sprite.setPosition(position);
	}

	if (status == dead) 
		return status = exploding;
	if (explosionFrame >= 10)
		return status = exploded;
	if (status == exploding)
		return status = exploding;

	if (position.x < -96 || position.x > 960 || position.y > 540 || position.y < -96)
		return status = outboard;
	if (hp <= 0) 
		return status = dead;

	return status = alive;
}

void Asteroid::setScale(){
	if (rand()%100 < 70)
		scale = 0.5;
	else 
		scale = 1; 
}

void Asteroid::getDamage(){
	hp--;
}

float Asteroid::getScale(){
	return scale;
}

int Asteroid::getReward(){
	return reward;
}

Sprite Asteroid::explosion(float time){
	int x = (int)explosionFrame%5;
	int y = (int)(explosionFrame/5);
	explosionSprite.setTextureRect(IntRect(x * 96, y * 96, 96, 96));
	explosionSprite.setPosition(position.x-size.x, position.y-size.y);
	explosionFrame += time*100;

	return explosionSprite;
}
 