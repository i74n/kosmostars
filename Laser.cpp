#include "Laser.h"
#include "Player.h"

Laser::Laser(const Player * player){
	makeTexture("images/bullet.png");

	setPosition(player->position.x + player->size.x,
		player->position.y + player->size.y/2 - this->size.y/2
	);
}

Status Laser::update(float time){
	if (status != del){
		position.x += 50*time*500;
		sprite.setPosition(position);
		status = (position.x > 960) ? del : stay;
	}
	return status;
}

void Laser::hit(){status = del;}
