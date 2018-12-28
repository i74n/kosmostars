#include "Game.h"
#include <list>
#include <cstdlib>
#include <ctime>

Game::Game(){}
Game::~Game(){}

void Game::play(){
	srand(time(NULL));
	VideoMode desktop = VideoMode::getDesktopMode();
	RenderWindow window(VideoMode(960, 540, desktop.bitsPerPixel), "COSMOSTARS");

	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 35);//создаем объект текст
	text.setColor(Color::Red);//покрасили текст в красный	

	Player* player = new Player;
	Map* map = new Map;

	std::list<Asteroid*> asteroids;
	std::list<Laser*> lasers;
	std::list<Bonus*> bonuses;

	Clock clock; 
	float asteroid_cooldown = 0;

	while (window.isOpen()){
		Event event;
		while (window.pollEvent(event)) 
			if (event.type == Event::Closed)
				window.close();

		window.clear();

		float time = clock.getElapsedTime().asSeconds();	

		map->update(time);

		window.draw(map->getSprite());
		window.draw(player->getSprite());

		if (player->update(time) == make)
			lasers.push_back(new Laser(player));

		for(auto bonus = bonuses.begin(); bonus != bonuses.end();){
			window.draw((*bonus)->getSprite());
			if ((*bonus)->update(time) == del)
				bonus = bonuses.erase(bonus);
			else if (player->intersects(*bonus)){
				player->setBuff((*bonus)->getBuff());
				bonus = bonuses.erase(bonus);
			}else bonus++;
		}

		for(auto laser = lasers.begin(); laser != lasers.end();){
			window.draw((*laser)->getSprite());
			if ((*laser)->update(time) == del)
				laser = lasers.erase(laser);
			else {
				for(auto asteroid = asteroids.begin(); asteroid != asteroids.end(); asteroid++)
					if ((*laser)->intersects(*asteroid)){
						(*asteroid)->getDamage();
						(*laser)->hit();
					}
				laser++;
			}
		}

		asteroid_cooldown += time;
		if (asteroid_cooldown > 0.3){
			asteroids.push_back(new Asteroid());
			asteroid_cooldown = 0;
		}

		for(auto asteroid = asteroids.begin(); asteroid != asteroids.end();){
			switch ((*asteroid)->update(time)){
			case outboard:
				player->setScores(-(*asteroid)->getReward());
				asteroid = asteroids.erase(asteroid);
				continue;
			case exploding:
				window.draw((*asteroid)->explosion(time));
				asteroid++;
				continue;
			case exploded:
				player->setScores((*asteroid)->getReward());
				if ((*asteroid)->getScale() == 0.25) 
					bonuses.push_back(new Bonus((*asteroid)->position));
				asteroid = asteroids.erase(asteroid);	
				continue;
			case dead:
				if ((*asteroid)->getScale() == 1) {
					asteroids.push_back(new Asteroid((*asteroid)->position.x, (*asteroid)->position.y, 4, -2));
					asteroids.push_back(new Asteroid((*asteroid)->position.x, (*asteroid)->position.y, 4, 2));
					asteroids.push_back(new Asteroid((*asteroid)->position.x, (*asteroid)->position.y, -4, -2));
					asteroids.push_back(new Asteroid((*asteroid)->position.x, (*asteroid)->position.y, -4, 2));
				}
				asteroid++;
				continue;
			case alive: 
				if (player->intersects(*asteroid)){
					player->setScores(-2*(*asteroid)->getReward());
					(*asteroid) -> hp = 0;	
				}else
					window.draw((*asteroid)->getSprite());
				asteroid++;
				break;
			}
		}

		text.setString("SCORES: " + player->getScores());
		text.setPosition(390, 0);
		window.draw(text);//

		window.display(); 
		clock.restart();
	}
}
