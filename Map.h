#pragma once
#include "Entity.h"

class Map : public Entity {
private:
    float displace;

public:
    Map(Image& image);
    Status update(float time);
    bool isAlive();
};