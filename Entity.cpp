#include "Entity.h"


void Entity::makeTexture(std::string path, float scale){
	texture.loadFromFile(path); // загружаем изображение игрока
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
	Vector2u size2u = texture.getSize();
	size.x = scale*size2u.x;
	size.y = scale*size2u.y;
}

void Entity::setPosition(float x, float y){
	position.x = x;
	position.y = y;
	sprite.setPosition(position);
}

Sprite Entity::getSprite(){
	return sprite;
}

bool Entity::intersects(Entity * obj){
	return this->getSprite().getGlobalBounds().intersects(
		obj->getSprite().getGlobalBounds()
	);		 
}
 