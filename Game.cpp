#include "Game.h"
#include <cstdlib>
#include <ctime>

Game::Game()
{
    srand(time(NULL));
    desktop = VideoMode::getDesktopMode();
    window.create(VideoMode(960, 540, desktop.bitsPerPixel), "COSMOSTARS");

    font.loadFromFile("FONT.ttf"); //передаем нашему шрифту файл шрифта
    text.setCharacterSize(40);
    text.setColor(Color::Red); //покрасили текст в красный
    text.setFont(font);

    asteroidImage.loadFromFile("images/asteroids.png");
    laserImage.loadFromFile("images/bullet.png");
    bonusImage.loadFromFile("images/bonuses.png");
    explosionImage.loadFromFile("images/explosion.png");
    playerImage.loadFromFile("images/ship.png");
    mapImage.loadFromFile("images/cosmos.png");

    player = new Player(playerImage);
    map = new Map(mapImage);
}

Game::~Game() {}

void Game::play()
{
    float asteroid_cooldown = 0;

    while (window.isOpen() && player->getStatus() != dead) {
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();

        window.clear();

        float time = clock.getElapsedTime().asSeconds();
        window.draw(map->getSprite());
        window.draw(player->getSprite());

        map->update(time);
        switch (player->update(time)) {
        case shoot:
            lasers.push_back(new Laser(laserImage, player));
            break;
        case DEMOLISH:
            for (auto asteroid = asteroids.begin(); asteroid != asteroids.end(); asteroid++)
                (*asteroid)->hp = 0;
            break;
        }
        for (auto bonus = bonuses.begin(); bonus != bonuses.end();) {
            window.draw((*bonus)->getSprite());
            if ((*bonus)->update(time) == outboard) {
                delete *bonus;
                bonus = bonuses.erase(bonus);
            }
            else if (player->intersects(*bonus)) {
                player->setBuff((*bonus)->getBuff());
                delete *bonus;
                bonus = bonuses.erase(bonus);
            }
            else
                bonus++;
        }

        for (auto laser = lasers.begin(); laser != lasers.end();) {
            window.draw((*laser)->getSprite());
            if ((*laser)->update(time) == del) {
                delete *laser;
                laser = lasers.erase(laser);
            }
            else {
                for (auto asteroid = asteroids.begin(); asteroid != asteroids.end(); asteroid++)
                    if ((*laser)->intersects(*asteroid)) {
                        (*asteroid)->getDamage();
                        (*laser)->hit();
                    }
                laser++;
            }
        }

        asteroid_cooldown += time;
        if (asteroid_cooldown > 0.25) {
            asteroids.push_back(new Asteroid(asteroidImage, explosionImage));
            asteroid_cooldown = 0;
        }

        for (auto asteroid = asteroids.begin(); asteroid != asteroids.end();) {
            switch ((*asteroid)->update(time)) {
            case outboard:
                player->setScores(-(*asteroid)->getReward());
                delete *asteroid;
                asteroid = asteroids.erase(asteroid);
                continue;
            case exploding:
                window.draw((*asteroid)->explosion(time));
                asteroid++;
                continue;
            case exploded:
                if ((*asteroid)->hp != 0)
                    player->setScores((*asteroid)->getReward());
                delete *asteroid;
                asteroid = asteroids.erase(asteroid);
                continue;
            case dead:
                if ((*asteroid)->getScale() == 1) {
                    int x = rand() % 4 + 1;
                    int y = rand() % 4 + 1;
                    asteroids.push_front(new Asteroid(asteroidImage, explosionImage, (*asteroid)->position.x + 24, (*asteroid)->position.y + 24, x, y));
                    asteroids.push_front(new Asteroid(asteroidImage, explosionImage, (*asteroid)->position.x + 24, (*asteroid)->position.y + 48, x, -y));
                    asteroids.push_front(new Asteroid(asteroidImage, explosionImage, (*asteroid)->position.x + 48, (*asteroid)->position.y + 24, -x, y));
                    asteroids.push_front(new Asteroid(asteroidImage, explosionImage, (*asteroid)->position.x + 48, (*asteroid)->position.y + 48, -x, -y));
                }
                if ((*asteroid)->getScale() == 0.25 && rand() % 5)
                    bonuses.push_back(new Bonus(bonusImage, (*asteroid)->position));
                asteroid++;
                continue;
            case alive:
                if (player->intersects(*asteroid)) {
                    player->setScores(-2 * (*asteroid)->getReward());
                    (*asteroid)->hp = 0;
                }
                else
                    window.draw((*asteroid)->getSprite());
                asteroid++;
                continue;
            }
        }

        text.setString("SCORES: " + player->getScores());
        text.setPosition(000, 0);
        window.draw(text);
        if (player->getBuff() != nobuff) {
            std::string buff;
            if (player->getBuff() == x2)
                buff = "X2";
            if (player->getBuff() == shield)
                buff = "SHIELD";
            text.setString(buff + " TIME: " + player->getBuffTimeLeft());
            text.setPosition(500, 0);
            window.draw(text);
        }
        window.display();
        clock.restart();
    }

    if (player->getStatus() == dead) {
        int i = 0;
        while (i++ < 1000)
            std::cout << "YOU LOSE ";
    }
}
