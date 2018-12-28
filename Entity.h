#pragma once

#include <SFML/Graphics.hpp>

enum Buff { demolisher,
    x2,
    shield,
    nobuff };

enum Status { del,
    alive,
    exploding,
    exploded,
    outboard,
    shoot,
    stay,
    dead,
    DEMOLISH };

using namespace sf;

class Entity {
protected:
    Texture texture;
    Sprite sprite;
    Status status;

public:
    Vector2f position;
    Vector2u size;

    void makeTexture(Image& image, int x, int y, float scale = 1);
    void makeTexture(Image& image);
    void setPosition(float x, float y);
    Sprite getSprite();
    bool intersects(Entity* obj);
    Status update(float);
};