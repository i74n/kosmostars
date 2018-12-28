#include "Entity.h"

void Entity::makeTexture(Image& image, int x, int y, float scale)
{
    texture.loadFromImage(image); // загружаем изображение игрока
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(x * 96, y * 96, 96, 96));
    sprite.setScale(scale, scale);
    size = texture.getSize();
    size.x *= scale;
    size.y *= scale;
}

void Entity::makeTexture(Image& image)
{
    texture.loadFromImage(image); // загружаем изображение игрока
    sprite.setTexture(texture);
    size = texture.getSize();
}

void Entity::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;
    sprite.setPosition(position);
}

Sprite Entity::getSprite()
{
    return sprite;
}

bool Entity::intersects(Entity* obj)
{
    return this->getSprite().getGlobalBounds().intersects(
        obj->getSprite().getGlobalBounds());
}
