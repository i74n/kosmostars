#pragma once
#include <string>
#include <SFML/Graphics.hpp>

enum Buff {x2, demolisher, shield};
enum Status { del, alive, exploding, exploded, outboard, make, stay, dead};

using namespace sf;

class Entity{
protected:	
	Texture texture;
	Sprite sprite;
	Status status;
public:
	Vector2f position;
	Vector2u size;

	void makeTexture(std::string path, float scale = 1);
	void setPosition(float x, float y);
	Sprite getSprite();
	bool intersects(Entity * obj);
	virtual Status update(float) = 0;
};