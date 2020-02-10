#include "GraphicBody.h"

SDL_Rect GraphicBody::addGraphics(SDL_Point size, b2Vec2 pos, SDL_Color color)
{
	_rect.w = size.x;
	_rect.h = size.y;
	_rect.x = pos.x * M2P - _rect.w / 2.0f;
	_rect.y = pos.y * M2P - _rect.h / 2.0f;
	_color = color;
	return _rect;
}

void GraphicBody::setPhysicPosition(b2Vec2 pos)
{
	_rect.x = pos.x * M2P - _rect.w / 2.0f;
	_rect.y = pos.y * M2P - _rect.h / 2.0f;
}

void GraphicBody::draw(SDL_Renderer* render)
{
	SDL_SetRenderDrawColor(render,_color.r,_color.g,_color.b,_color.a);
	SDL_RenderFillRect(render,&_rect);
}
