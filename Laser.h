#pragma once
#include "Player.h"
#include "Entity.h"

class Laser : public Entity {
public:
    Laser(Image& image, const Player* player);
    Status update(float time);
    void hit();
};