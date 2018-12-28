#pragma once
#include <string>
#include <list>

#include "Entity.h"
#include "Map.h"
#include "Player.h"
#include "Laser.h"
#include "Asteroid.h"
#include "Bonus.h"

using namespace sf;

class Game{
	VideoMode desktop;
	RenderWindow window;

	Font font;
	Text text;

	Clock clock; 

	Player * player;
	Map * map;

	Image asteroidImage;
	Image laserImage;
	Image bonusImage;
	Image explosionImage;
	Image playerImage;
	Image mapImage;

	std::list<Asteroid*> asteroids;
	std::list<Laser*> lasers;
	std::list<Bonus*> bonuses;
public:
	Game();
	~Game();
	void play();
};