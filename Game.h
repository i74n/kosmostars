#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Asteroid.h"
#include "Map.h"
using namespace sf;

class Game{
public:
	Game();
	~Game();
	void play();
};