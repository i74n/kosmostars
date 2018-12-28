#include "Bonus.h"

Bonus::Bonus(Vector2f playerPose){
	buff = static_cast<Buff>(rand()%2);
	std::string img;
	switch(buff){
	case x2: 
		img = "x2.png"; break;
	case demolisher: 
		img = "demolisher.png";break;
	case shield: 
		img = "shield.png";break;
	}
	makeTexture("images/" + img, 0.5);
	setPosition(playerPose.x+16, playerPose.y+16);
}

Status Bonus::update(float time){
	position.x -= time*1000;
	sprite.setPosition(position);

	if (position.x < -96){
		return del;
	}
	return stay;
}


Buff Bonus::getBuff(){return buff;}
 