#include "Entity.h"

void Entity::makeTexture(Image & image, int x, int y, float scale){
	texture.loadFromImage(image); // загружаем изображение игрока
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(x*96, y*96, 96, 96));
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
 