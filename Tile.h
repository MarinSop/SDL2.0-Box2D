#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
class Tile
{
public:
	Tile(SDL_Point tilesize,int id,SDL_Point screenpos);
	~Tile();
	  
	void cout();

	int ID;
	SDL_Rect* screenPos;
	SDL_Rect* tilePos;
};

