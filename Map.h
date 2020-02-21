#pragma once
#include "tinyxml2.h"
#include "box2d/box2d.h"
#include "Body.h"
#include <iostream>
#include <vector>
#include <string>
#include "Tilemap.h"
#include "Teleporter.h"
using namespace tinyxml2;

class Map
{
public:
	Map();
	~Map();

	bool load(b2World* world, SDL_Renderer* renderer, std::string fileNum);
	void update(Player& player);
	void draw(SDL_Renderer* renderer);

	void reset();


	std::vector<Body*> getDynamicBodies();
	std::vector<Body*> getBarrierBodies();

	b2Vec2 startingPos;

	SDL_Rect* getFinishPos();

private:
	b2World* _world;
	SDL_Renderer* _renderer;
	XMLDocument doc;
	SDL_Point _mapSize;
	SDL_Point _tileSize;
	std::vector<Body*> _static;
	std::vector<Body*> _dynamic;
	std::vector<Body*> _barrier;
	std::vector<Teleporter*> _teleporter;
	GraphicBody* _finish;
	std::string _barrierStr;
	std::string _groundStr;

	Tilemap* _tilemap;

	int _currentLevel = 1;


};

