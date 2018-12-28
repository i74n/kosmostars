#include "Bonus.h"

Bonus::Bonus(Image & image, Vector2f playerPose){
	makeTexture(image, buff = static_cast<Buff>(rand()%3), 0, 0.5);
	setPosition(playerPose.x+16, playerPose.y+16);
}

Status Bonus::update(float time){
	position.x -= time*1000;
	sprite.setPosition(position);

	if (position.x < -96){
		return outboard;
	}
	return stay;
}

Buff Bonus::getBuff(){
	return buff;
}
 