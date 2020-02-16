#pragma once
#include "tinyxml2.h"
#include "box2d/box2d.h"
#include "Body.h"
#include <iostream>
#include <vector>
#include <string>
#include "Tilemap.h"
using namespace tinyxml2;

class Map
{
public:
	Map();
	~Map();

	bool load(b2World* world, SDL_Renderer* renderer);
	void update();
	void draw(SDL_Renderer* renderer);
	std::vector<Body*> getDynamicBodies();

private:
	XMLDocument doc;
	SDL_Point _mapSize = {32,24};
	SDL_Point _tileSize = { 32,32 };
	std::vector<Body*> _static;
	std::vector<Body*> _dynamic;
	std::string _backgroundStr;
	std::string _groundStr;

	Tilemap* _tilemap;

};

