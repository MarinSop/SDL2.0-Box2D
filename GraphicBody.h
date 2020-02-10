#pragma once
#include "SDL.h"
#include "box2d/box2d.h"

#define M2P 30.0f
#define P2M 1/M2P
class GraphicBody
{
public:
	SDL_Rect addGraphics(SDL_Point size, b2Vec2 pos, SDL_Color color);
	void setPhysicPosition(b2Vec2 pos);
	void draw(SDL_Renderer* render);
private:
	SDL_Rect _rect;
	SDL_Color _color;
};

