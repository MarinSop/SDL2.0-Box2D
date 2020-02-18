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
	GraphicBody();
	~GraphicBody();
	void addGraphics(SDL_Renderer* renderer, SDL_Point size, b2Vec2 pos, SDL_Point tileSize, int id);
	void setPhysicPosition(b2Vec2 pos, float angle);
	void draw(SDL_Renderer* render, SDL_Texture* tex);
	SDL_Rect* getGamePos();
private:

	SDL_Rect* _gamePos = new SDL_Rect();
	SDL_Rect* _tilePos = new SDL_Rect();
	float _angle = 0;

	b2Vec2 imageTilePos(int id);
};

