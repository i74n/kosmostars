#include "Asteroid.h"

Asteroid::Asteroid(Image & image, Image & explosionImage){
	explosionFrame = 0; 
	setScale();

	hp = 4*scale;
	speed.x = 2/scale;
	speed.y = 0;
	reward = 12*scale;
	
	makeTexture(image, rand()%3, 0, scale);

	setPosition(900, rand()%(540-size.x));

	explosionTexture.loadFromImage(explosionImage);
	explosionSprite.setTexture(explosionTexture);
	explosionSprite.setScale(scale, scale); 
}

Asteroid::Asteroid(Image & image, Image & explosionImage, float x, float y, float speedX, float speedY){
	explosionFrame = 0; 
	scale = 0.25;

	hp = 1;
	speed.x = speedX;
	speed.y = speedY;
	reward = 3;

	makeTexture(image, rand()%3, 0, scale);

	setPosition(x, y);

	explosionTexture.loadFromImage(explosionImage);
	explosionSprite.setTexture(explosionTexture);
	explosionSprite.setScale(0.75, 0.75); 
}

Status Asteroid::update(float time){
	if (status == dead) 
		return status = exploding;
	if (status == alive){
		position.x -= speed.x*time*500;
		position.y -= speed.y*time*500;
		sprite.setPosition(position);
	}
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
	scale = (rand()%100 < 70) ? 0.5 : 1;
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
	explosionSprite.setPosition(position.x, position.y);
	explosionFrame += time*100;

	return explosionSprite;
}
 