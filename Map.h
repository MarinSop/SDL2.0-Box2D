#pragma once
#include "tinyxml2.h"
#include "box2d/box2d.h"
#include "Body.h"
#include <iostream>
#include <vector>
#include <string>
using namespace tinyxml2;

class Map
{
public:
	Map();
	~Map();

	bool load(b2World* world);
	void update();
	void draw(SDL_Renderer* renderer);

private:
	XMLDocument doc;
	std::vector<Body*> _static;
	std::vector<Body*> _dynamic;
	std::string _backgroundStr;
	std::string _groundStr;
};

