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
	void addTexture(SDL_Renderer* renderer, const char* path);
	void setPhysicPosition(b2Vec2 pos, float angle);
	void draw(SDL_Renderer* render, SDL_Texture* tex);
	void drawWithAddedTex(SDL_Renderer* renderer);
	SDL_Rect* getGamePos();
private:

	SDL_Rect* _gamePos;
	SDL_Rect* _tilePos;
	float _angle = 0;
	SDL_Texture* _tex = nullptr;

	b2Vec2 imageTilePos(int id);
};

