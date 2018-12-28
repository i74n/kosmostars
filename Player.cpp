#include "Player.h"
#include <sstream>

Player::Player(){
	scores = 1000;
	shot_cooldown = 0;
	makeTexture("images/ship.png");
	setPosition(0, 270);
}

Status Player::update(float time){
	shot_cooldown += time;

	if (position.y > 0 && Keyboard::isKeyPressed(Keyboard::Up))
		position.y -= 0.5*time*10000;
	else if (position.y + size.y < 540 && Keyboard::isKeyPressed(Keyboard::Down)) 
		position.y += 0.5*time*10000;
	else if (Keyboard::isKeyPressed(Keyboard::Space) && shot_cooldown > 0.05){
		shot_cooldown = 0;
		return make;
	}
	sprite.setPosition(position);

	return stay;
}

void Player::setBuff(Buff buff){
	switch (buff){
	case x2: 
		break;
	case demolisher: 
		break;
	case shield: 
		break;
	}
}

std::string Player::getScores(){
	std::stringstream ss;
	ss << scores;
	return ss.str();
}

void Player::setScores(int crement){
	scores += crement;
}
