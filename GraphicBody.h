#pragma once
#include "SDL.h"
#include "box2d/box2d.h"
#include "SDL_image.h"
#include <iostream>

#define M2P 30.0f
#define P2M 1/M2P
class GraphicBody
{
public:
	void addGraphics(SDL_Renderer* renderer, SDL_Point size, b2Vec2 pos, SDL_Point tileSize, int id);
	void setPhysicPosition(b2Vec2 pos);
	void draw(SDL_Renderer* render, SDL_Texture* tex);
private:

	SDL_Rect* _gamePos = new SDL_Rect();
	SDL_Rect* _tilePos = new SDL_Rect();
	float angle = 0;

	b2Vec2 imageTilePos(int id);
};

