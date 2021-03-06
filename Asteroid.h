#pragma once
#include "Entity.h"

class Asteroid : public Entity {
private:
    int reward;
    Texture explosionTexture;
    Sprite explosionSprite;
    float explosionFrame;
    float scale;
    Vector2f speed;
    Status status;

public:
    int hp;
    Asteroid(Image& image, Image& explosionImage);
    Asteroid(Image& image, Image& explosionImage, float x, float y, float speedX, float speedY);
    Status update(float time);
    void setScale();
    float getScale();
    void getDamage();
    int getReward();
    Sprite explosion(float time);
};