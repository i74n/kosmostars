#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "Entity.h"
#include "Map.h"
#include "Player.h"
#include "Laser.h"
#include "Asteroid.h"
#include "Bonus.h"

using namespace sf;

class Game{
public:
	Game();
	~Game();
	void play();
};