#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
class Tile
{
public:
	Tile(SDL_Point tilesize,int id,SDL_Point screenpos);
	~Tile();

	int ID;
	SDL_Point screenPos;
	SDL_Point tilePos;
	SDL_Point tileSize;
};

