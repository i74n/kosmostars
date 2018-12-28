#include "Map.h"

Map::Map(){
	makeTexture("images/cosmos.png", 1);
	displace = 0;
}

Status Map::update(float time){
	displace += time*1000;
	if (displace >= 960)
		displace = 0;

	setPosition(-displace, 0);

	return stay;
}

 